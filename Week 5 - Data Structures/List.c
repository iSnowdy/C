#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const int SIZE = 3;  // Size of the array

    // Allocate memory for the list
    int *list = malloc(SIZE * sizeof(int));
    if (list == NULL) {  // Check if malloc failed
        printf("Memory allocation failed\n");
        return 1;
    }

    // Input values
    for (int i = 0; i < SIZE; i++) {
        printf("Number: ");
        scanf("%i", &list[i]);
    }

    // Outputs
    for (int i = 0; i < SIZE; i++) {
        printf("%i\n", list[i]);
    }

    // But now I want space for more than 3 numbers. How do I do it?
    int *tmp = malloc((SIZE + 1) * sizeof(int));
    if (tmp == NULL) {
        free(list);
        printf("Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < SIZE; i++) {
        tmp[i] = list[i];
    }
    printf("New number: ");
    scanf("%i", &tmp[3]);
    // Free the allocated memory of the original list
    free(list);
    // Now list is freed, only composed of garbage value
    // But now we want to get back our original list
    list = tmp;
    free(tmp);
    // End of program
    free(list);
    return 0;
}
