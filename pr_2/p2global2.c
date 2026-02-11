#include <stdio.h>

void function() {
    int local_array[1000];
    int local_init_array[1000] = { 1 };
}

int main() {
    function();
    printf("Hello World\n");
    return 0;
}