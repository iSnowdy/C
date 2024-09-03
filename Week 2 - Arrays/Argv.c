#include <stdio.h>
#include <string.h>

int main(int argc, char argv[]) {
    if (argc != 2) {
        printf("Invalid input. Please try again\n");
        return 1;
    }

    for (int i = 0; i < argc; i ++) {
        printf("argv[%i] is %s\n", i, argv[i]);
    }
}