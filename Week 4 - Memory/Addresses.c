#include <stdio.h>
#include <string.h>

int main(void) {
    int n = 50;
    printf("%i\n", n);
    printf("%p\n", &n); // & = address of / * = go to that memory direction / with "p" we can reference to & and/or *

    // C supports pointers. A point is basically an address of some variable that we can also store in a variable.
    // Lets create a pointer to store the address of some value

    int *p = &n; // Store the address of the integer n in p. Declaring a pointer with a type
    printf("%p\n", p); // Does the same, but now we don't need to specify &n because we already stored it previously
    printf("----\n");

    // Now lets go to the address of n, and tell me what is there
    printf("%i\n", *p); // * means go to that value and show what is there. Here, although its the same symbol, it means go to that pointer, not declaring it like in line 11

    char *s = "HI!";
    printf("%s\n", s);
    printf("%p\n", s);
    printf("%p\n", &s[0]); // Its the same value of p* s because the cs50.h library returns the pointer of the string
    printf("%p\n", &s[strlen(s) - 1]);

    char *c = "HI!"; // Compiler sees "..." as a & to assign memory of a sequence of characters, akka a String in C
    printf("%s\n", c);
    printf("----\n");

    printf("%c\n", c[0]);
    printf("%c\n", c[1]);
    printf("%c\n", c[2]);
    printf("%c\n", c[3]); // Null point character that determines the end of the char *
    // But we know that *p is a pointer that directs you to the start of the sequence of characters, in this case. Therefore:

    printf("%c\n", *c); // Would be the same as c[0]. Furthermore, if we add pointer arithmetic into this...
    printf("%c\n", *(c + 1));
    printf("%c\n", *(c + 2)); // So when the compiler sees c[3], it translates it to *(c + 2)
}
