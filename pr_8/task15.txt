#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/syscall.h>
#include <unistd.h>

#ifndef RENAME_EXCHANGE
#define RENAME_EXCHANGE (1 << 1)
#endif

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Використання: %s <файл1> <файл2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *file1 = argv[1];
    const char *file2 = argv[2];

    long ret = syscall(SYS_renameat2, AT_FDCWD, file1, AT_FDCWD, file2, RENAME_EXCHANGE);

    if (ret == 0) {
        printf("Файли '%s' та '%s' успішно та атомарно обміняно місцями.\n", file1, file2);
    } else {
        perror("Помилка обміну (renameat2 RENAME_EXCHANGE)");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}