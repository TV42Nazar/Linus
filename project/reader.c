#include "common.h"

int main() {
    int shm_fd;
    SensorData *shared_data;
    sem_t *sem_ready;

    // 1. Відкриття існуючого семафора
    sem_ready = sem_open(SEM_READY_NAME, 0);
    if (sem_ready == SEM_FAILED) {
        perror("Помилка sem_open (спочатку запустіть письменника)");
        exit(EXIT_FAILURE);
    }

    // 2. Відкриття існуючої спільної пам'яті (тільки для читання)
    shm_fd = shm_open(SHM_NAME, O_RDONLY, 0666);
    if (shm_fd == -1) {
        perror("Помилка shm_open");
        exit(EXIT_FAILURE);
    }

    // 3. Відображення пам'яті (тільки PROT_READ)
    shared_data = mmap(NULL, sizeof(SensorData), PROT_READ, MAP_SHARED, shm_fd, 0);
    if (shared_data == MAP_FAILED) {
        perror("Помилка mmap");
        exit(EXIT_FAILURE);
    }

    // 4. Очікування даних
    printf("[Читач] Очікування запису даних письменником...\n");
    sem_wait(sem_ready); // Процес блокується, поки семафор дорівнює 0

    // 5. Зчитування та вивід даних
    printf("\n--- Отримані дані ---\n");
    printf("Температура: %.1f C\n", shared_data->temperature);
    printf("Напруга: %.1f В\n", shared_data->voltage);
    printf("Статус: %s\n", shared_data->device_status ? "OK" : "Помилка");
    printf("Повідомлення: %s\n", shared_data->message);
    printf("---------------------\n\n");

    // 6. Звільнення локальних ресурсів
    munmap(shared_data, sizeof(SensorData));
    close(shm_fd);
    sem_close(sem_ready);

    // 7. Видалення об'єктів з системи (робиться лише один раз)
    shm_unlink(SHM_NAME);
    sem_unlink(SEM_READY_NAME);
    printf("[Читач] Ресурси успішно видалені з системи.\n");

    return 0;
}