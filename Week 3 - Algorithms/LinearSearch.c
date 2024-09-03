#include <stdio.h>
#include <string.h>

typedef struct {
    char *name;
    char *number;
}
person; // people[i].name ...

int main(void)
{
    int numbers[] = {20, 500, 10, 5, 100, 1, 50};
    int length = sizeof(numbers) / sizeof(numbers[0]);
    /*
     C does not know automatically the length of arrays. So we must
     calculate it. Knowing the size of the array in bytes, divided by one
     of its element, we can know the size
     So dividing the total memory size of the array by a single
     element, we can get the number of elements stored
     That works because teh total size in bytes divided by the size of
     one element gives us how many of such element (any kind) can fit into
     that total space
    */

    int n = get_int("Number: ");

    for (int i = 0; i < length; i ++) { // Linear search; O(n); u(1)
        if (numbers[i] == n) {
            printf("Found\n");
            return 0; // Success
        } else {
            printf("Not found in position %i\n", i);
        }
    }
    printf("Not found anywhere\n");

    printf("Now for strings...\n\n");

    char *selection[] = {"battleship", "boot", "cannon", "iron", "thimble", "top hat"};
    char *word = get_string("Word: ");
    int len = sizeof(selection) / sizeof(selection[0]);

    for (int i = 0; i < len; i ++) {
        if (strcmp(selection[i], word) == 0) { // If strcmp returns 0, its true. strcmp also does an ASCII comparison
            printf("Match at %i\n", i);
            return 1; // True
        }
    }
    printf("No string matches\n");
    return 0; // False 
}
