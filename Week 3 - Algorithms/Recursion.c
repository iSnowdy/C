#include <stdio.h>

void draw(int n);

int main(void)
{
    int height = get_int("Height: ");
    draw(height);
}

void draw(int n)
{
    // Base case
    if (n <= 0) {
        return;
    }
    // Print pyramid of height n -1
    draw(n - 1);

    // Print one more row of the pyramid
    for(int i = 0; i < n; i++) {
        printf("#");
    }
    printf("\n");
}
