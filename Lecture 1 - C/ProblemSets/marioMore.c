#include <stdio.h>

// Functions
int askHeight(void);
void printRows(int length);
void printSpaces(int length);

int main(void)
{
    int height = askHeight();
    int counter = height;
    for (int i = 0; i < height; i ++) {
        printSpaces(counter - 1);
        printRows(i + 1);
        printf("  "); // Space in between the pyramids
        printRows(i + 1);
        printf("\n");
        counter --; // Reduces the number of spaces of the left pyramid
    }
}

// Asks the user for a height
// However, it must be an int between 1 and 8 (inclusive)
int askHeight(void)
{
    int a;
    do {
        printf("Height? \n");
        scanf("%i", &a);
    }
    while (1 > a || a > 8); // do-while used to make sure we have the input we need
    return a;
}

// Prints the blocks from top to bottom
void printRows(int length)
{
    for (int i = 0; i < length; i ++) {
        printf("#");
    }
}

// Adds spaces to the left pyramid
void printSpaces(int length)
{
    for (int i = 0; i < length; i ++) {
        printf(" ");
    }
}
