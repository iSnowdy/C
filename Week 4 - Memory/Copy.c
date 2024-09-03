#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main (void) {
    char *s = get_string("s: ");
    char *t = s; // Would this copy a string?

    t[0] = toupper(t[0]); // Capitalize the first letter of t, which should be the same as s
    printf("%s\n", s);
    printf("%s\n", t);
    // So because the address is the same, both pointers are pointing at the same thing: s. So
    // when we modify t, we are also modifying s

    // So how do we really copy a string? malloc and free
    // malloc allocates the space in memory to a variable and returns the address dedicated for that new variable

    char *a = get_string("a: ");

    if (s == NULL) { // Read below (the get_string can also return NULL just like malloc)
        return 1;
    }

    const int len = strlen(a);
    char *b = malloc(len + 1); // + 1 because we also want the null character that is at the end of Strings

    if (b == NULL) {
        return 1;
        // This basically means that if malloc returns NULL; it means that there is not enough memory available
        // to allocate to our variable. So if that were to be the case, just preemptively abort the program
    }

    for (int i = 0; i < len + 1; i++) {
        b[i] = a[i];
    }
    // t[len + 1] = '\0'; if we do not do i < len + 1 in the for loop (or <=)

    // But like for everything that is very commonly used, there's a function to copy strings called
    // strcpy(a, b) where the first argument is the direction to copy to and the second argument what to copy
    // a = destination, b = source

    if (strlen(b) > 0 ) { // Avoid possible cases where the user does not input any string
        b[0] = toupper(b[0]);
    }

    printf("%s\n", a);
    printf("%s\n", b);

    // When we are back using memory, we need to give back the memory to it. free is used for it (opposite of malloc)

    free(b); // No need to free up memory from the get_string variables; its already been done
    return 0;
}
