#include <stdio.h>
#include <stdlib.h>

int main() {
    void *p = realloc(NULL, 100);
    printf("realloc(NULL) = %p\n", p);
    p = realloc(p, 0);
    printf("realloc(p, 0) = %p\n", p);
    return 0;
}