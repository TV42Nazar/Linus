#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

int main() {
    DIR *dir = opendir(".");
    if (!dir) { perror("opendir"); return EXIT_FAILURE; }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        // Перевіряємо, чи файл закінчується на .c
        char *ext = strrchr(entry->d_name, '.');
        if (ext && strcmp(ext, ".c") == 0) {
            printf("Надати дозвіл на читання іншим для файлу %s? (y/n): ", entry->d_name);
            char answer;
            scanf(" %c", &answer);
            
            if (answer == 'y' || answer == 'Y') {
                struct stat st;
                if (stat(entry->d_name, &st) == 0) {
                    // Додаємо S_IROTH (дозволяє читання для Others)
                    if (chmod(entry->d_name, st.st_mode | S_IROTH) == 0) {
                        printf("Дозвіл надано.\n");
                    } else {
                        perror("chmod");
                    }
                }
            }
        }
    }
    closedir(dir);
    return EXIT_SUCCESS;
}