#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>

void print_permissions(mode_t mode) {
    printf("%c", S_ISDIR(mode) ? 'd' : (S_ISLNK(mode) ? 'l' : '-'));
    printf("%c%c%c", (mode & S_IRUSR) ? 'r' : '-', (mode & S_IWUSR) ? 'w' : '-', (mode & S_IXUSR) ? 'x' : '-');
    printf("%c%c%c", (mode & S_IRGRP) ? 'r' : '-', (mode & S_IWGRP) ? 'w' : '-', (mode & S_IXGRP) ? 'x' : '-');
    printf("%c%c%c ", (mode & S_IROTH) ? 'r' : '-', (mode & S_IWOTH) ? 'w' : '-', (mode & S_IXOTH) ? 'x' : '-');
}

int main() {
    DIR *dir = opendir(".");
    if (!dir) { perror("opendir"); return EXIT_FAILURE; }

    struct dirent *entry;
    struct stat file_stat;

    while ((entry = readdir(dir)) != NULL) {
        if (stat(entry->d_name, &file_stat) == -1) continue;

        print_permissions(file_stat.st_mode);
        printf("%ld ", (long)file_stat.st_nlink);

        struct passwd *pw = getpwuid(file_stat.st_uid);
        struct group *gr = getgrgid(file_stat.st_gid);
        printf("%s %s ", pw ? pw->pw_name : "unknown", gr ? gr->gr_name : "unknown");

        printf("%5ld ", (long)file_stat.st_size);

        char time_buf[64];
        struct tm *tm_info = localtime(&file_stat.st_mtime);
        strftime(time_buf, sizeof(time_buf), "%b %d %H:%M", tm_info);
        printf("%s %s\n", time_buf, entry->d_name);
    }
    closedir(dir);
    return EXIT_SUCCESS;
}