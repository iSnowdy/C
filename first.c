#include <stdio.h>

int main(void) {
    char name[50];
    int age;

    printf("Enter your name: ");
    scanf("%s", name);
    printf("Enter your age: ");
    scanf("%d", &age);

    if (age < 18) {
        printf("Not allowed here! You are %d! Get out of here %s", age, name);
    } else {
        printf("Hello, World! You are: %d and your name is %s", age, name);
    }
    return 0;
}