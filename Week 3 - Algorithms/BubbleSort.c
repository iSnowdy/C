#include <stdio.h>

int main(void) {
    const int size = 6; // 5 2 1 3 6 4
    int numbers[size];

    for (int i = 0; i < size; i ++) {
        int a = get_int("Number: ");
        numbers[i] = a;
    }

    int swapCounter = 1;
    while (swapCounter != 0) { // So that it only sorts if a swap has been made, avoiding unnecesary iterations
        swapCounter = 0;
        for (int i = 0; i < size - 2; i ++) {
            if (numbers[i] > numbers[i + 1]) {
                int temp = numbers[i];
                numbers[i] = numbers[i + 1];
                numbers[i + 1] = temp;
                swapCounter++;
            }
            // printf("i is %i\n", i);
        }
    }
    for (int i = 0; i < size; i ++) {
    printf("%i\n", numbers[i]);
    }
}
