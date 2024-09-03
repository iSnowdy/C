#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Invalid input. Please try again\n");
        return 1;
    }

    for (int i = 0; i < argc; i ++) {
        printf("argv[%i] is %s\n", i, argv[i]);
    }

    // We convert the height inside the String to an int to be able to use it
    int height = atoi(argv[1]);
    printf("Height prompted by the user is %i\n", height);
}
