#include <stdio.h>
#include <stdint.h>

int main() {
    printf("Архітектура: %ld-біт\n", sizeof(void*) * 8);
    printf("Максимальне значення size_t: %zu\n", SIZE_MAX);
    return 0;
}#include <stdio.h>
#include <stdlib.h>

int main() {
    int xa = 1000000, xb = 1000000;
    int num = xa * xb;
    printf("Результат множення (int): %d\n", num);
    printf("Розмір як size_t: %zu\n", (size_t)num);
    
    void *ptr = malloc(num);
    if (!ptr) printf("Результат: malloc повернув NULL\n");
    else free(ptr);
    return 0;
}