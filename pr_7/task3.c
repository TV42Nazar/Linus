#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Використання: %s <слово> <файл>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[2], "r");
    if (!file) { perror("fopen"); return EXIT_FAILURE; }

    char line[2048];
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, argv[1]) != NULL) {
            printf("%s", line);
        }
    }

    fclose(file);
    return EXIT_SUCCESS;
}