#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Використання: %s <файл1> [файл2 ...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    int line_count = 0;
    for (int i = 1; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");
        if (!file) { perror("fopen"); continue; }

        char line[2048];
        while (fgets(line, sizeof(line), file)) {
            printf("%s", line);
            line_count++;
            
            if (line_count % 20 == 0) {
                printf("--- Натисніть Enter для продовження ---");
                getchar();
            }
        }
        fclose(file);
    }
    return EXIT_SUCCESS;
}