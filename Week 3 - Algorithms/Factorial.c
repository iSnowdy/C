#include <stdio.h>

int fact(int a);

int main(void) {
    int n;

    do {
        n = get_int("Number > 0: ");
    } while (n < 0);

    printf("Factorial of %i is %i\n", n, fact(n));
}

int fact(int a) {
    if (a == 1) { // Base Case
        return 1;
    }
    return a * fact(a - 1); // Recursive Call
}
