#include <stdlib.h>
#include <stdio.h>

typedef struct node { // node is called here so we can define node as part of the struct
    int number;
    struct node *next;
} node;

int main(int argc, char *argv[]) {
    node *list = NULL;

    for (int i = 1; i < argc; i++) {
        // printf("%s\n", argv[i]); // Values are String type
        int number = atoi(argv[i]); // Convert that String type to int

        node *n = malloc(sizeof(node)); // Gives us a chunk of memory to fit something in a node
        if (n == NULL) {
            printf("Memory allocation failed\n");
            return 1;
        }
        n -> number = number;
        // n is pointing at a chunk of memory big enough to fit a number
        // n -> number goes to that chunk of number and update it with = number
        n -> next = NULL; // Initialized to NULL
        // Now we need to link the list to the node
        n -> next = list; // So that we do not leave numbers with no pointers
        list = n; // Now we can tell the list where the number is
    }
    // Now what about printing the whole list
    // A pointer pointing to the list itself. And since arrays pointers always
    // point to the first element, we do no need to specify that
    node *ptr = list;
    while (ptr != NULL) { // As long as that pointer is not at the end of the list...
        printf("%i\n", ptr -> number);
        ptr = ptr -> next;
    }
    // When we do n -> next = list while building the list, we are inserting the new
    // elements to the front of the list, therefore, it prints from 'last' to 'first'
    // preappending
}
