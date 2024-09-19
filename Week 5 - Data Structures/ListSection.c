#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct node {
    char *phrase;
    struct node *next;
} node;

#define listSize 3

int unload(node *list);
void visualizer(node *list);

int main(void) {
    node *list = NULL;

    // Adding items to the list
    for (int i = 0; i < listSize; i++) {
        printf("Sentence: ");
        char *phrase = malloc(100 * sizeof(char));
        if (phrase == NULL) {
            printf("Memory allocation failure\n");
            return 1;
        }
        scanf("%99s", phrase);
        // Allocate memory for a node
        node *n = malloc(sizeof(node));
        if (n == NULL) {
            printf("Memory allocation failure\n");
            free(phrase);
            return 1;
        }
        // Now that we have space in memory, we populate each element in the node
        n -> phrase = phrase;
        n -> next = NULL; // Yet to point to something else. Good practice to first point to NULL

        n -> next = list; // So we can keep adding new nodes without losing information
        list = n; // So that the list keeps growing
        // Pre appending
        visualizer(list);
    }
    if (unload(list) != 1) {
        printf("Error freeing list\n");
        return 1;
    } else {
        printf("Freed the list\n");
        return 0;
    }
}

// Frees all memory previously allocated with malloc
int unload(node *list) {
    node *ptr = list; // Pointer to move around the list

    while (ptr != NULL) {
        ptr = list -> next; // To keep track of the next node
        free(list -> phrase); // Frees phrase malloc
        free(list); // Now, that we have a pointer of the next node, we can free the current one
        list = ptr; // We get back the data of the next node temporarily pointed to with ptr
    }
    return 1;
}

// Prints the information inside the linked list
void visualizer(node *list) {
    printf("\n+--- List Visualizer ---+\n\n");
    while (list != NULL) {
        printf("Location: %p\n", list);  // Print the current node's address
        printf("Phrase: '%s'\n", list -> phrase); // Print the phrase stored in the node
        printf("Next: %p\n\n", list -> next); // Print the address of the next node

        list = list -> next;  // Move to the next node
    }
    printf("\n+-----------------+\n");
}
