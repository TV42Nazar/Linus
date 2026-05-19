#include "common.h"

int main() {
    int shm_fd;
    SensorData *shared_data;
    sem_t *sem_ready;

    // 1. Створення семафора з початковим значенням 0
    // O_CREAT створює семафор, якщо його не існує
    sem_ready = sem_open(SEM_READY_NAME, O_CREAT, 0666, 0);
    if (sem_ready == SEM_FAILED) {
        perror("Помилка sem_open");
        exit(EXIT_FAILURE);
    }

    // 2. Створення об'єкта спільної пам'яті
    // O_CREAT | O_RDWR дозволяє створення та читання/запис
    shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("Помилка shm_open");
        exit(EXIT_FAILURE);
    }

    // 3. Встановлення розміру спільної пам'яті
    if (ftruncate(shm_fd, sizeof(SensorData)) == -1) {
        perror("Помилка ftruncate");
        exit(EXIT_FAILURE);
    }

    // 4. Відображення пам'яті в адресний простір процесу
    shared_data = mmap(NULL, sizeof(SensorData), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shared_data == MAP_FAILED) {
        perror("Помилка mmap");
        exit(EXIT_FAILURE);
    }

    // 5. Запис даних
    printf("[Письменник] Запис даних...\n");
    shared_data->temperature = 42.5f;
    shared_data->voltage = 12.3f;
    shared_data->device_status = 1;
    strncpy(shared_data->message, "Всі системи працюють у штатному режимі.", sizeof(shared_data->message) - 1);
    
    sleep(2); // Імітація тривалої роботи датчика
    printf("[Письменник] Дані успішно записані.\n");

    // 6. Відправка сигналу читачу (збільшення значення семафора)
    sem_post(sem_ready);
    printf("[Письменник] Сигнал готовності відправлено.\n");

    // 7. Звільнення локальних ресурсів
    munmap(shared_data, sizeof(SensorData));
    close(shm_fd);
    sem_close(sem_ready);

    return 0;
}