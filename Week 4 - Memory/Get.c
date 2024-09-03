#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int n;
    printf("n: ");
    scanf("%i", &n); // We give the address of n
    printf("%i\n", n);
    // That is how we get user's input for ints without cs50.h library (although without error handling)

    char s[4]; // Hi!
    printf("Sentence: ");
    scanf("%s", s); // A string is already an address of the first character of the sequence; therefore the neediness of &
    printf("%s\n", s);

    // But you can never know the length of the string a user is going to input. So that must be handled by allocating more and more memory
    // depending on the user's input (malloc)
}
