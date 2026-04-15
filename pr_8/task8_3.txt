#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

long long comp_count = 0;

int compare(const void *a, const void *b) {
    comp_count++;
    int int_a = *(const int *)a;
    int int_b = *(const int *)b;
    return (int_a > int_b) - (int_a < int_b);
}

void assert_sorted(int *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        assert(arr[i] <= arr[i + 1]);
    }
}

void run_test(const char* test_name, int *arr, int n) {
    comp_count = 0;
    qsort(arr, n, sizeof(int), compare);
    assert_sorted(arr, n);
    printf("Тест: %-15s | Елементів: %d | К-сть порівнянь: %lld\n", test_name, n, comp_count);
}

int main() {
    int n = 50000;
    int *arr = malloc(n * sizeof(int));
    srand(time(NULL));

    for(int i=0; i<n; i++) arr[i] = rand() % n;
    run_test("Випадковий", arr, n);

    for(int i=0; i<n; i++) arr[i] = i;
    run_test("Відсортований", arr, n);

    for(int i=0; i<n; i++) arr[i] = n - i;
    run_test("Зворотний", arr, n);

    for(int i=0; i<n; i++) arr[i] = 42;
    run_test("Однакові ел.", arr, n);

    free(arr);
    printf("\nУсі тести пройдено успішно. Функція qsort працює коректно.\n");
    return EXIT_SUCCESS;
}