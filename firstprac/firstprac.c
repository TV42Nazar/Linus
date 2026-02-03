#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

typedef struct {
    int value; 
    int count; 
} Item;

int comparator(const void* a, const void* b) {
    const Item* aitem = (const Item*)a;
    const Item* bitem = (const Item*)b;
    
    if (aitem->value == bitem->value) {
        return bitem->count - aitem->count; 
    }
    return aitem->value - bitem->value; 
}

void merge(Item arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    Item Le[n1], Ri[n2]; 

    for (i = 0; i < n1; i++) Le[i] = arr[l + i];
    for (j = 0; j < n2; j++) Ri[j] = arr[m + 1 + j];

    i = 0; j = 0; k = l;
    
    while (i < n1 && j < n2) {
        if (comparator(&Le[i], &Ri[j]) <= 0) {
            arr[k] = Le[i]; i++;
        } else {
            arr[k] = Ri[j]; j++;
        }
        k++;
    }
    while (i < n1) { arr[k] = Le[i]; i++; k++; }
    while (j < n2) { arr[k] = Ri[j]; j++; k++; }
}

void mergeSort(Item arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        //добавляємо в пул розпаралелених задач
        #pragma omp task shared(arr)
        mergeSort(arr, l, m);

        #pragma omp task shared(arr)
        mergeSort(arr, m + 1, r);
        //чекаємо завершення синхронізації
        #pragma omp taskwait
        merge(arr, l, m, r);
    }
}


void heapify(Item arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1; 
    int right = 2 * i + 2; 

    if (left < n && comparator(&arr[left], &arr[largest]) > 0)
        largest = left;

    if (right < n && comparator(&arr[right], &arr[largest]) > 0)
        largest = right;

    // Якщо найбільший не корінь
    if (largest != i) {
        Item temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        heapify(arr, n, largest);
    }
}

void heapSort(Item arr[], int n) {
    // 1. Побудова купи (перегрупування масиву)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        Item temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify(arr, i, 0);
    }
}

int main(int argc, char* argv[]) {
    char* type = "qsort"; 
    
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
    else if (strcmp(type, "heap") == 0) {
        heapSort(arr, size);
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
