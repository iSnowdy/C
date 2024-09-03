#include <stdio.h>

int binarySearch(int array[], int size, int target);

int main(void) {
    const int size = 6; // 5 2 1 3 6 4
    int numbers[size];

    for (int i = 0; i < size; i++) {
        int a = get_int("Number: ");
        numbers[i] = a;
    }

    // Sort the array before performing binary search (necessary for binary search to work correctly)
    // Bubble Sort method
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            if (numbers[j] > numbers[j + 1]) {
                int temp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp;
            }
        }
    }

    printf("Sorted array:\n");
    for (int i = 0; i < size; i++) {
        printf("%i\n", numbers[i]);
    }

    int target = get_int("Enter the number to search for: ");

    if (binarySearch(numbers, size, target) == 1) {
        printf("Number found!\n");
    } else {
        printf("Number not found.\n");
    }
}

int binarySearch(int array[], int size, int target) {
    int start = 0;
    int end = size - 1;

    while (start <= end) {
        int mid = start + (end - start) / 2;

        if (array[mid] == target) {
            return 1;  // Target found true
        } else if (target < array[mid]) {
            end = mid - 1;  // Search in the left half
        } else {
            start = mid + 1;  // Search in the right half
        }
    }

    return 0;  // Target not found false
}
