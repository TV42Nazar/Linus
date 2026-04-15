#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *rwho_fp = popen("rwho", "r");
    FILE *more_fp = popen("more", "w");

    if (rwho_fp == NULL || more_fp == NULL) {
        perror("Помилка popen");
        return EXIT_FAILURE;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), rwho_fp) != NULL) {
        fputs(buffer, more_fp);
    }

    pclose(rwho_fp);
    pclose(more_fp);
    return EXIT_SUCCESS;
}