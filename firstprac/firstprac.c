#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

// Структура для імітації складних даних
typedef struct {
    int value; // Значення (первинний ключ)
    int count; // Частота (вторинний ключ)
} Item;

// Компаратор: спочатку за value (зростання), потім за count (спадання)
// Використовуємо const void*, щоб qsort не сварився (warning)
int comparator(const void* a, const void* b) {
    const Item* aitem = (const Item*)a;
    const Item* bitem = (const Item*)b;
    
    if (aitem->value == bitem->value) {
        return bitem->count - aitem->count; // Спадання для частоти
    }
    return aitem->value - bitem->value; // Зростання для значення
}

// Функція злиття двох підмасивів
void merge(Item arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Створюємо тимчасові масиви типу Item
    Item Le[n1], Ri[n2]; 

    for (i = 0; i < n1; i++) Le[i] = arr[l + i];
    for (j = 0; j < n2; j++) Ri[j] = arr[m + 1 + j];

    i = 0; 
    j = 0; 
    k = l;
    
    while (i < n1 && j < n2) {
        // Передаємо адреси елементів у компаратор
        if (comparator(&Le[i], &Ri[j]) <= 0) {
            arr[k] = Le[i];
            i++;
        } else {
            arr[k] = Ri[j];
            j++;
        }
        k++;
    }

    // Копіюємо залишки, якщо є
    while (i < n1) {
        arr[k] = Le[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = Ri[j];
        j++;
        k++;
    }
}

// Рекурсивне сортування злиттям з OpenMP Tasks
void mergeSort(Item arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        // Створюємо завдання для потоків 
        #pragma omp task shared(arr)
        mergeSort(arr, l, m);

        #pragma omp task shared(arr)
        mergeSort(arr, m + 1, r);

        // Чекаємо завершення сортування обох частин
        #pragma omp taskwait
        merge(arr, l, m, r);
    }
}

int main(int argc, char* argv[]) {
    char* type = "qsort"; // Дефолтний метод
    
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-t") == 0 && i + 1 < argc) {
            type = argv[i + 1];
        }
    }

    Item arr[] = {{6, 1}, {7, 2}, {8, 1}, {9, 1}, {0, 6}, {7, 7}, {0, 5}, {1, 2}, {3, 4}};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Метод сортування: %s\n", type);

    if (strcmp(type, "qsort") == 0) {
        qsort(arr, size, sizeof(Item), comparator);
    } 
    else if (strcmp(type, "merge") == 0) {
        #pragma omp parallel
        {
            #pragma omp single
            mergeSort(arr, 0, size - 1);
        }
    }
    else {
        printf("Невідомий метод! Використовую qsort.\n");
        qsort(arr, size, sizeof(Item), comparator);
    }

    for (int i = 0; i < size; i++) {
        printf("{Val:%d, Count:%d} ", arr[i].value, arr[i].count);
    }
    printf("\n");

    return 0;
}