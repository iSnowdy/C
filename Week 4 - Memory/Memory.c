#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int *x = malloc(sizeof(int)); // Allocate to the address x 4 bytes with malloc (instead of just int x)

    int *a = malloc(3 * sizeof(int)); // 3 * sizeof(int) is basically an array
    a[1] = 72; // Should've been a[0]
    a[2] = 73;
    a[3] = 74;

    // And we also did not free up the memory allocated. And we could compile it. (free(x); free(a);)
    // With a tool like valgrind, this can be avoided
    // it will show 3 errors: 2 for the allocation and not free'd memory (memory leak) of x and a, and a third one for the writing out of index for a
}
