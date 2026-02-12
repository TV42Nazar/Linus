#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

void cpu_limit_handler(int signum) {
    const char *msg = "\n\n!!! CATCH SIGXCPU !!! Time limit exceeded.\n";
    write(STDOUT_FILENO, msg, strlen(msg));
    
    _exit(0);
}

void shuffle(int *array, int n) {
    if (n > 1) {
        for (int i = 0; i < n - 1; i++) {
            int j = i + rand() / (RAND_MAX / (n - i) + 1);
            int t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}

int main() {
    signal(SIGXCPU, cpu_limit_handler);

    srand(time(NULL));
    int lotto49[49];
    int lotto36[36];
    long count = 0;

    printf("Starting CPU heavy task...\n");

    while (1) {
        for(int i=0; i<49; i++) lotto49[i] = i+1;
        for(int i=0; i<36; i++) lotto36[i] = i+1;

        shuffle(lotto49, 49);
        shuffle(lotto36, 36);

        count++;
        if (count % 100000 == 0) {
            write(STDOUT_FILENO, ".", 1);
        }
    }
    return 0;
}