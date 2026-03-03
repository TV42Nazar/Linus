#include <stdio.h>
#include <stdlib.h>

int main() {
    void *ptr = malloc(0);
    printf("Вказівник: %p\n", ptr);
    free(ptr);
    return 0;
}