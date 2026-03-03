#include <stdio.h>
#include <stdlib.h>

void *__real_malloc(size_t size);
void __real_free(void *ptr);

#define MAX_ALLOCS 1000
struct {
    void *ptr;
    size_t size;
    int is_freed;
} alloc_log[MAX_ALLOCS];

int alloc_count = 0;

void *__wrap_malloc(size_t size) {
    void *ptr = __real_malloc(size); 
    
    if (alloc_count < MAX_ALLOCS && ptr != NULL) {
        alloc_log[alloc_count].ptr = ptr;
        alloc_log[alloc_count].size = size;
        alloc_log[alloc_count].is_freed = 0;
        alloc_count++;
    }
    
    printf("[LOG] Виділено %zu байт за адресою %p\n", size, ptr);
    return ptr;
}

void __wrap_free(void *ptr) {
    if (ptr != NULL) {
        for (int i = 0; i < alloc_count; i++) {
            if (alloc_log[i].ptr == ptr && !alloc_log[i].is_freed) {
                alloc_log[i].is_freed = 1;
                break;
            }
        }
        printf("[LOG] Звільнено пам'ять за адресою %p\n", ptr);
    }
    
    __real_free(ptr);
}

void check_leaks() {
    int leaks = 0;
    printf("\n========================================\n");
    printf("        ЗВІТ ПРО ВИТОКИ ПАМ'ЯТІ         \n");
    printf("========================================\n");
    
    for (int i = 0; i < alloc_count; i++) {
        if (!alloc_log[i].is_freed) {
            printf("[УВАГА! ВИТІК] Адреса: %p, Розмір: %zu байт\n", 
                   alloc_log[i].ptr, alloc_log[i].size);
            leaks++;
        }
    }
    
    if (leaks == 0) {
        printf("Витоків не виявлено. Уся пам'ять звільнена коректно!\n");
    } else {
        printf("Знайдено витоків: %d\n", leaks);
    }
    printf("========================================\n");
}

int main() {
    printf("--- Запуск тестової програми ---\n\n");

    void *ptr1 = malloc(100);
    free(ptr1);

    void *ptr2 = malloc(256);
    void *ptr3 = malloc(512);
    
    free(ptr2);

    printf("\n--- Завершення програми ---\n");
    
    check_leaks();

    return 0;
}