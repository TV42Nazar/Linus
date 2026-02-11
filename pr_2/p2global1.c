#include <stdio.h>
#include <string.h>
#include <time.h>

int main(int argc, char* argv[]) {
    int bits64 = 64;
    int bits32 = 32;
    time_t maxNum;
    char* type = "32";
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-t") == 0 && i + 1 < argc) {
            type = argv[i + 1];
        }
    }
    if ((strcmp(type, "64") == 0)) {
        maxNum = ((time_t)1 << (bits64 - 1)) - 1;
    }
    else {
        maxNum = ((time_t)1 << (bits32 - 1)) - 1;
    }

    char* x = ctime(&maxNum);

    if (x == NULL) {
        printf("too big!\n");
        printf("time_t: %lld\n", (long long)maxNum);
    }
    else {
        printf(": %s", x);
    }

    return 0;
}