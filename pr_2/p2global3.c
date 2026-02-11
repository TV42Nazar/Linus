#include <stdio.h>
#include <stdlib.h>

// 1. DATA (Global Initialized)
int data_var = 10;

// 2. BSS (Global Uninitialized)
int bss_var;

// Function to check stack growth direction
void check_stack(int *parent) {
    int child;
    printf("Stack (child):  %p\n", &child);
    
    // Compare addresses
    if (&child < parent) 
        printf("-> CONCLUSION: Stack grows DOWN (addresses decrease)\n");
    else 
        printf("-> CONCLUSION: Stack grows UP (addresses increase)\n");
}

int main() {
    
    printf("Text Segment:   %p  (Address of main)\n", main);
    
    printf("Data Segment:   %p  (Global initialized)\n", &data_var);
    printf("BSS Segment:    %p  (Global uninitialized)\n", &bss_var);

    int *heap = (int*)malloc(sizeof(int));
    printf("Heap Segment:   %p  (from malloc)\n", heap);

    int stack;
    printf("Stack (parent): %p  (Local variable)\n", &stack);

    check_stack(&stack);
    
    free(heap);
    return 0;
}