#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

int main() {
    struct timeval start, end;

    gettimeofday(&start, NULL);

    sleep(1);
    for (volatile int i = 0; i < 10000000; i++); 

    gettimeofday(&end, NULL);

    long seconds = end.tv_sec - start.tv_sec;
    long microseconds = end.tv_usec - start.tv_usec;
    double elapsed_ms = (seconds * 1000.0) + (microseconds / 1000.0);

    printf("Час виконання: %.3f мс\n", elapsed_ms);

    return EXIT_SUCCESS;
}