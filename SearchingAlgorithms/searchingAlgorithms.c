#include "sortingAlgorithms.h"
#include <stdio.h>
#include <stdbool.h>

static void PrintArray(int *array, int length)
{
    for (int i = 0; i < length; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void LinearSearch(void) 
{
    int array[] = {64, 34, 25, 12, 22, 11, 90, 5};
    int length = sizeof(array) / sizeof(array[0]);
    int targetValue = 22;

    printf("Original array: ");
    PrintArray(array, length);
    printf("Target value: %d\n", targetValue);

    for (int i=0; i < length; i++)
    {
        if (array[i] == targetValue) {
            printf("%d found at index %d\n", array[i], i);
            return;
        }
    }

    printf("Target value %d not found\n", targetValue);
}

void BinarySearch(void)
{
    int array[] = {5, 11, 12, 22, 25, 34, 64, 90};   // Binary search requires a sorted array
    int length = sizeof(array) / sizeof(array[0]);
    int targetValue = 22;

    printf("Original array: ");
    PrintArray(array, length);
    printf("Target value: %d\n", targetValue);

    int low = 0;
    int high = length - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;   // Avoids potential overflow compared to (low + high) / 2

        if (array[mid] == targetValue) {
            printf("%d found at index %d\n", array[mid], mid);
            return;
        }
        else if (array[mid] < targetValue) {
            low = mid + 1;   // Search the right half
        }
        else {
            high = mid - 1;  // Search the left half
        }
    }

    printf("Target value %d not found\n", targetValue);
}