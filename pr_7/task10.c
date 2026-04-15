#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    srand(time(NULL) ^ getpid());

    float n = 10.5;
    if (argc > 1) n = atof(argv[1]);

    printf("Випадкові числа [0.0; 1.0]:\n");
    for (int i = 0; i < 5; i++) {
        float r = (float)rand() / (float)RAND_MAX;
        printf("%.4f\n", r);
    }

    printf("\nВипадкові числа [0.0; %.2f]:\n", n);
    for (int i = 0; i < 5; i++) {
        float r = ((float)rand() / (float)RAND_MAX) * n;
        printf("%.4f\n", r);
    }

    return EXIT_SUCCESS;
}