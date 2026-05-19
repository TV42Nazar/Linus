#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>      // Константи O_*
#include <sys/stat.h>   // Константи режимів доступу
#include <sys/mman.h>   // Функції спільної пам'яті (mmap, shm_open)
#include <unistd.h>     // Функції ftruncate, close
#include <semaphore.h>  // POSIX семафори

// Унікальні імена для об'єктів у системі
#define SHM_NAME "/my_sensor_shared_memory"
#define SEM_READY_NAME "/my_sensor_sem_ready"

// Структура даних для передачі
typedef struct {
    float temperature;
    float voltage;
    int device_status; // 1 - OK, 0 - Помилка
    char message[256];
} SensorData;

#endif