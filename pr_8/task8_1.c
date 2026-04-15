#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return EXIT_FAILURE;
    }

    int flags = fcntl(pipefd[1], F_GETFL);
    fcntl(pipefd[1], F_SETFL, flags | O_NONBLOCK);

    int nbytes = 100000;
    char *buffer = malloc(nbytes);
    
    printf("Спроба записати %d байт у pipe...\n", nbytes);
    ssize_t count = write(pipefd[1], buffer, nbytes);

    if (count != nbytes) {
        printf("Частковий запис! Запитано: %d, фактично записано: %zd\n", nbytes, count);
    } else {
        printf("Записано успішно: %zd байт\n", count);
    }

    free(buffer);
    close(pipefd[0]);
    close(pipefd[1]);
    return EXIT_SUCCESS;
}