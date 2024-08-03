#include <stdio.h>

// We can think of for loops as an old writing machine. Where each line is checked, and once it is done, then it
// jumps to the next one. There, it once again, reads the whole line, and then jump to the next one. And so on.

int askLines(void);

int main (void) {
    int n = askLines();

    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < n; j ++) {
            printf("*");
        }
        printf("\n");
    }
}

int askLines(void) {
    int n;
    printf("How many lines?");
    scanf("%d", &n);
    return n;
}