#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

int is_dir(const struct dirent *entry) {
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) return 0;
    
    struct stat st;
    if (stat(entry->d_name, &st) == 0 && S_ISDIR(st.st_mode)) return 1;
    return 0;
}

int main() {
    struct dirent **namelist;
    int n = scandir(".", &namelist, is_dir, alphasort);

    if (n < 0) {
        perror("scandir");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < n; i++) {
        printf("%s/\n", namelist[i]->d_name);
        free(namelist[i]);
    }
    free(namelist);
    return EXIT_SUCCESS;
}