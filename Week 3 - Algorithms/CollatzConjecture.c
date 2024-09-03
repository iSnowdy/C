#include <stdio.h>

int collatz(int n);

int main(void) {
    int n = get_int("Number: ");
    printf("Start at %i, it took %i steps to get to 1\n", n, collatz(n));
}

int collatz(int n) {
    int steps = 0;

    if (n == 1) { // Base Case
        return steps;
    } else if ((n % 2) == 0) { // Even
        steps ++;
        return steps + collatz(n/2);
    } else { // Odd
        steps ++;
        return steps + collatz(3 * n + 1);
    }
}
