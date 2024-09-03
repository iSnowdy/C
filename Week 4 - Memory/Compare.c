#include <stdio.h>
#include <string.h>

int main(void) {
    int a = get_int("a: ");
    int b = get_int("b: ");

    if (a == b) {
        printf("Same\n");
    } else {
        printf("Different\n");
    }
    // But what goes on inside the computer's memory for this code?

    char *s = get_string("s: ");
    char *t = get_string("t: ");

    if (s == t) { // We are basically comparing the addresses of each char *. So it will always be different
        printf("Same\n");
    } else {
        printf("Different\n");
    }

    // Therefore, we need to compare the 'thing' that is being addressed, not the pointer itself

    if (strcmp(s, t) == 0) { // Comparisong char by char
        printf("Same\n");
    } else {
        printf("Different\n");
    }

    printf("----\n");

    printf("%s\n", s);
    printf("%s\n", t);
    // Lets see their address
    printf("%p\n", s);
    printf("%p\n", t);
    // We can see they are actually different. So no way they would be the same if compared with only ==
}
