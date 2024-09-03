#include <stdio.h>
#include <string.h>

int main (void) {
    char *phrase = get_string("Phrase to analyze: ");

    for (int i = 0, n = strlen(phrase); i < n - 1; i ++) {
        if (phrase[i] > phrase[i + 1]) {
            printf("It is not in alphabetical order\n");
            return 0;
        }
    }
    printf("Succeeded\n");
    return 0;
}
