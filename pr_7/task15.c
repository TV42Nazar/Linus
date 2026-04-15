#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>

#define MAX_USERS 1000

typedef struct {
    char name[256];
    int shared_groups_count;
    char shared_groups_names[1024];
} SharedUser;

SharedUser shared_users[MAX_USERS];
int shared_users_count = 0;

void add_shared_user(const char *username, const char *groupname) {
    for (int i = 0; i < shared_users_count; ++i) {
        if (strcmp(shared_users[i].name, username) == 0) {
            shared_users[i].shared_groups_count++;
            strcat(shared_users[i].shared_groups_names, ", ");
            strcat(shared_users[i].shared_groups_names, groupname);
            return;
        }
    }
    if (shared_users_count < MAX_USERS) {
        strncpy(shared_users[shared_users_count].name, username, 255);
        shared_users[shared_users_count].shared_groups_count = 1;
        strncpy(shared_users[shared_users_count].shared_groups_names, groupname, 1023);
        shared_users_count++;
    }
}

int main() {
    uid_t uid = getuid();
    struct passwd *pw = getpwuid(uid);
    if (!pw) return EXIT_FAILURE;

    printf("Користувач: %s (UID: %d)\n", pw->pw_name, uid);

    int ngroups = 0;
    getgrouplist(pw->pw_name, pw->pw_gid, NULL, &ngroups);
    gid_t *groups = malloc(ngroups * sizeof(gid_t));
    getgrouplist(pw->pw_name, pw->pw_gid, groups, &ngroups);

    printf("\n=== Ієрархія груп ===\n");
    for (int i = 0; i < ngroups; i++) {
        struct group *gr = getgrgid(groups[i]);
        if (!gr) continue;

        printf("[%s група] %s (GID: %d)\n  Учасники: ",
              (groups[i] == pw->pw_gid) ? "Первинна" : "Додаткова", gr->gr_name, groups[i]);

        int has_members = 0;
        for (char **mem = gr->gr_mem; *mem != NULL; mem++) {
            printf("%s ", *mem);
            has_members = 1;
            if (strcmp(*mem, pw->pw_name) != 0) add_shared_user(*mem, gr->gr_name);
        }
        if (!has_members) printf("(Немає додаткових)");
        printf("\n\n");
    }

    printf("=== Перетин груп ===\n");
    int found = 0;
    for (int i = 0; i < shared_users_count; i++) {
        printf("- %s: %d спільна(і) група(и) [%s]\n",
               shared_users[i].name, shared_users[i].shared_groups_count, shared_users[i].shared_groups_names);
        found = 1;
    }
    if (!found) printf("Немає перетинів з іншими користувачами.\n");

    free(groups);
    return EXIT_SUCCESS;
}