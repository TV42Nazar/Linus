#include <stdio.h>
#include <stdint.h>

int main() {
    printf("Архітектура: %ld-біт\n", sizeof(void*) * 8);
    printf("Максимальне значення size_t: %zu\n", SIZE_MAX);
    return 0;
}