#include <stdio.h>

void meow(void);
void advancedMeow(int n);

int main(void) {
    /*int i = 3;
    while (i > 0) {
        meow();
        i--;
    }
    */

   advancedMeow(5);

    for (int j = 0; j < 3; j ++) printf("Iteration number: %d\n", j);
}

void meow(void) {
    printf("Meow!\n");
}

void advancedMeow(int n) {
    for (int i = 0; i < n; i ++) {
        printf("Meowww! - Said cat number %d\n", i);
    }
}
