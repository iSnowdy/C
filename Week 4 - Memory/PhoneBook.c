#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    FILE *file = fopen("phonebook.csv", "a"); // "r" for reading noly, "w" for writing (overwrites), "a" for appending (adding to the file)
    // FILE *file is a pointer to that file

    if ( file == NULL) { // Always, when dealing with pointers, handle NULL cases
        return 1;
    }

    char *name = get_string("Name: ");
    char *number = get_string("Number: ");

    fprintf(file, "%s, %s\n", name, number); // Printing to that file

    fclose(file); // Close the file (always)

}
