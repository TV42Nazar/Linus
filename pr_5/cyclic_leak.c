#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

int main() {
    Node* nodeA = (Node*)malloc(sizeof(Node));
    Node* nodeB = (Node*)malloc(sizeof(Node));

    if (!nodeA || !nodeB) {
        return 1;
    }

    nodeA->data = 10;
    nodeB->data = 20;

    nodeA->next = nodeB;
    nodeB->next = nodeA;

    free(nodeA);
    nodeB = NULL;

    return 0;
}