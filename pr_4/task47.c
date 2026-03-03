#include <stdlib.h>

struct sbar { int data[10]; };

int main() {
    struct sbar *ptr = calloc(1000, sizeof(struct sbar));
    struct sbar *newptr = reallocarray(ptr, 500, sizeof(struct sbar));
    if (newptr) ptr = newptr;
    free(ptr);
    return 0;
}