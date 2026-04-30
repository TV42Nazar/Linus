#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    // Масив із затримками для кожного процесу
    int delays[] = {3, 1, 2}; 
    int n = 3;
    pid_t pid;

    printf("=== [Батько] PID: %d. Починаю створювати процеси... ===\n\n", getpid());

    for (int i = 0; i < n; i++) {
        pid = fork();

        if (pid < 0) {
            perror("Помилка створення процесу");
            exit(1);
        }

        if (pid == 0) {
            // Код дочірнього процесу
            int my_delay = delays[i];
            printf("[Дитина] PID: %d створено. Чекаю %d сек.\n", getpid(), my_delay);
            sleep(my_delay);
            printf("[Дитина] PID: %d закінчив роботу.\n", getpid());
            exit(0);
        }
    }

    // Код батьківського процесу
    printf("\n[Батько] Очікую на завершення всіх дітей через wait()...\n\n");

    for (int i = 0; i < n; i++) {
        int status;
        // wait() повертає PID першого завершеного процесу
        pid_t finished_pid = wait(&status);
        printf("[Батько] Побачив завершення PID: %d\n", finished_pid);
    }

    printf("\n=== [Батько] Всі процеси зібрано. Завершення. ===\n");
    return 0;
}