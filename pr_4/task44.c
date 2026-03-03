#include <stdlib.h>
#include <stdio.h>

int main() {
    void *ptr = NULL;
    for (int i = 0; i < 2; i++) {
        if (!ptr) {
            ptr = malloc(10);
            printf("Крок %d: Виділено %p\n", i, ptr);
        }
        free(ptr);
        // ПРАВИЛЬНИЙ ВАРІАНТ: ptr = NULL; 
        printf("Крок %d: Звільнено %p\n", i, ptr);
    }
    return 0;
}