#include <stdio.h>

int askNumber(void);
int sumNumbers(int a, int b);

int main(void) {
    int firstNumber = askNumber();
    int secondNumber = askNumber();
    printf("The sum of numbers %d and %d is %d\n",
        firstNumber, secondNumber, sumNumbers(firstNumber, secondNumber));
}

int askNumber(void) {
    int a;
    printf("Insert a number:");
    scanf("%d", &a);
    return a;
}

int sumNumbers(int a, int b) {
    return a + b;
}