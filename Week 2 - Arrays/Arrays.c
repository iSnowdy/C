#include <stdio.h>
#include <string.h>

int main(void) {
    
    int numberStorage[10];
    int a = get_int("Initial number: ");
    numberStorage[0] = a;

    for (int i = 1, n = get_int("How many numbers? "); i < n; i ++) {
        numberStorage[i] = numberStorage[i - 1] * 2;
    }

    char *phrase = get_string("Enter a phrase now: ");

    for (int i = 0, length = strlen(phrase); i < length; i ++) {
        printf("%c", phrase[i]);
    }
    printf("\n");

    // printf("Here: %li", sizeof(numberStorage));
}
