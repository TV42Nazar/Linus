#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    void *ptr = malloc(100);
    void *tmp = realloc(ptr, SIZE_MAX);
    if (tmp == NULL) {
        printf("realloc повернув NULL. Стара пам'ять %p збережена.\n", ptr);
        free(ptr);
    }
    return 0;
}