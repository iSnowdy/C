#include <stdlib.h>
#include <stdio.h>

typedef struct node { // node is called here so we can define node as part of the struct
    int number;
    struct node *next;
} node;

int main(int argc, char *argv[]) {
    // Memory for numbers
    node *list = NULL;

    // for-each CLA
    for (int i = 1; i < argc; i++) {
        // Convert argument to int
        int number = atoi(argv[i]);

        // Allocate node's memory
        node *n = malloc(sizeof(node));
        if (n == NULL) {
            printf("Memory allocation has failed\n");
            return 1;
        }
        n -> number = number;
        n -> next = NULL;

        if (list == NULL) { // if the list is empty...
            list = n;
        } else if (n -> number < list -> number) { // To insert in order
            n -> next = list;
            list = n;
        } else { // But maybe the number belongs later in the list, not at the start
            for (node *ptr = list; ptr != NULL; ptr = ptr -> next) {
                if (ptr -> next == NULL) { // if we are at the end of the list...
                    ptr -> next = n; // append the node
                    break;
                }
                // if the number is in the middle of the list...
                if (n -> number < ptr -> next -> number) {
                    // if the new node's number (n -> number) is less than (<) the number
                    // in the next node (ptr -> next)
                    n -> next = ptr -> next; // Updates the new node next pointer to be equal to whatever node I'm pointing at next pointer
                    ptr -> next = n; // Pointer updated to point the current one
                    break;
                }
            }
        }
        // Now, instead of preaappending, we are appending. So with each insert,
        // we have to find the end of the list and then insert the new value there
        // So the Big O is no longer O(1), but O(n)
    }
}
