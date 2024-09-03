#include <stdio.h>

int main(void) {
    const int size = 6; // 5 2 1 3 6 4
    int numbers[size];

    for (int i = 0; i < size; i ++) {
        int a = get_int("Number: ");
        numbers[i] = a;
    }

    for (int i = 0; i < size - 1; i ++) {
        int smallestIndex = i; // We assume the first element of the unsorted array is the smallest

        for (int j = i + 1; j < size; j ++) { // We now iterate to find a smaller element
            if (numbers[j] < numbers[smallestIndex]) {
                smallestIndex = j;
            }
        }

        if (smallestIndex != i) { // Only swap if a smaller element was found
            int temp = numbers[i];
            numbers[i] = numbers[smallestIndex];
            numbers[smallestIndex] = temp;
        }

    }
    for (int i = 0; i < size; i ++) {
    printf("%i\n", numbers[i]);
    }
}
