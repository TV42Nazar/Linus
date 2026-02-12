#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    FILE *fptr = fopen("result.txt", "w");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    srand(time(NULL));

    int count = 0;
    while (1) {
        int roll = (rand() % 6) + 1;
        
        int result = fprintf(fptr, "Rolled: %d\n", roll);
        
        if (result < 0) {
            printf("\nError writing file!\n");
            perror("Cause"); 
            break;
        }

        count++;
        if (count % 1000 == 0) {
            fflush(fptr);
            printf("n: %d\n", count);
        }
    }

    fclose(fptr);
    return 0;
}