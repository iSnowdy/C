#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct node {
    char *phrase;
    struct node *next;
} node;

node *table[26]; // Alphabet

int hash(char *phrase);
int unload(node *list);
void visualizer(node *list);

int main(void) {
    // Add items
    for (int i = 0; i < 3; i++) {
        printf("Sentence: ");
        char *phrase = malloc(100 * sizeof(char));
        if (phrase == NULL) {
            printf("Memory allocation has failed\n");
            return 1;
        }
        scanf("%99s", phrase);

        int bucket = hash(phrase);
        printf("%s hashes to %i\n", phrase, bucket);
    }
}

// A good hash function always returns the same value for the same input. Produces even
// distribution across all buckets and uses all buckets (buckets meaning spaces)
int hash(char *phrase) {
    return toupper(phrase[0]) - 'A'; // To get the first character of the word
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
