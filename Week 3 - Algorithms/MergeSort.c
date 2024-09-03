#include <stdio.h>

// Functions
void merge(int array[], int left, int mid, int right);
void mergeSort(int array[], int left, int right);

int main(void) {
    const int size = 6; // 5 2 1 3 6 4
    int numbers[size];

    for (int i = 0; i < size; i++) {
        int a = get_int("Number: ");
        numbers[i] = a;
    }

    mergeSort(numbers, 0, size - 1);

    for (int i = 0; i < size; i++) {
        printf("%i\n", numbers[i]);
    }
}

void merge(int array[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int leftArray[n1], rightArray[n2];

    // We copy the data to temp arrays
    for (int i = 0; i < n1; i++) {
        leftArray[i] = array[left + i];
    }
    for (int j = 0; j < n2; j++) {
        rightArray[j] = array[mid + 1 + j];
    }

    // Merging the temp arrays back into the original array
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArray[i] <= rightArray[j]) {
            array[k] = leftArray[i];
            i++;
        } else {
            array[k] = rightArray[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of leftArray[]
    while (i < n1) {
        array[k] = leftArray[i];
        i++;
        k++;
    }

    // Copy the remaining elements of rightArray[]
    while (j < n2) {
        array[k] = rightArray[j];
        j++;
        k++;
    }
}

void mergeSort(int array[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(array, left, mid);
        mergeSort(array, mid + 1, right);
        merge(array, left, mid, right);
    }
}
