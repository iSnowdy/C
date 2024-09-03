#include <stdlib.h>
#include <stdio.h>

void swap(int *a, int *b);

int main(void) {
    int x = 1;
    int y = 2;

    printf("X is %i and Y is %i\n", x, y);
    printf("Swapping them now...\n");
    swap(&x, &y); // & to give the address of x and y 
    printf("X is %i and Y is %i\n", x, y);
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
