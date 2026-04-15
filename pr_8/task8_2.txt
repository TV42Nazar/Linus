#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    char data[] = {4, 5, 2, 2, 3, 3, 7, 9, 1, 5};
    char buffer[4];

    int fd = open("test_bytes.bin", O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (fd == -1) { perror("open"); return EXIT_FAILURE; }
    write(fd, data, sizeof(data));

    lseek(fd, 3, SEEK_SET);

    ssize_t bytes_read = read(fd, buffer, 4);

    printf("Зчитано %zd байти. Вміст буфера: ", bytes_read);
    for (int i = 0; i < bytes_read; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");

    close(fd);
    unlink("test_bytes.bin");
    return EXIT_SUCCESS;
}