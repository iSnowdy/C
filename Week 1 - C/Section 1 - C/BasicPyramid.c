#include <stdio.h>

int askHeight(void);
void printRow(int length);

int main(void) {
    int height = askHeight();

    for (int i = 0; i < height; i ++) {
        printRow(i + 1);
    }
}

int askHeight(void) {
    int a;
    printf("Choose your height: ");
    scanf("%i", &a);
    return a;
}

void printRow(int length) {
    for (int i = 0; i < length; i ++) {
        printf("#");
    }
    printf("\n");
}