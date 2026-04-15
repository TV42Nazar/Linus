#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int main() {
    DIR *dir = opendir(".");
    if (!dir) { perror("opendir"); return EXIT_FAILURE; }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;

        struct stat st;
        if (stat(entry->d_name, &st) == 0 && S_ISREG(st.st_mode)) { 
            printf("Видалити файл %s? (y/n): ", entry->d_name);
            char answer;
            scanf(" %c", &answer);
            
            if (answer == 'y' || answer == 'Y') {
                if (unlink(entry->d_name) == 0) {
                    printf("Видалено.\n");
                } else {
                    perror("unlink");
                }
            }
        }
    }
    closedir(dir);
    return EXIT_SUCCESS;
}