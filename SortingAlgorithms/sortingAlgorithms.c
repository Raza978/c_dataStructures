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

void BubbleSort(void) 
{
    int array[] = {64, 34, 25, 12, 22, 11, 90, 5};
    int length = sizeof(array) / sizeof(array[0]);

    printf("Original array: ");
    PrintArray(array, length);

    for (int i=0; i < length-1; i++)    // traverse the whole array n-1 times
    {
        // length-i-1 to avoid comparing already sorted elements at the end of the array.
        for (int j=0; j < length-i-1; j++)  // traverse the array and put the largest unsorted element in its sorted position.
        {
            if (array[j] > array[j+1])
            {
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }

    printf("Sorted array: ");
    PrintArray(array, length);
}

void SelectionSort(void)
{
    int array[] = {64, 34, 25, 12, 22, 11, 90, 5};
    int length = sizeof(array) / sizeof(array[0]);

    printf("Original array: ");
    PrintArray(array, length);

    int minIndex;
    for (int i=0; i < length-1; i++)    // traverse the whole array n-1 times
    {
        minIndex = i;

        // j=i+1 to avoid comparing already sorted elements at the beginning of the array.
        for (int j=i+1; j < length; j++)    // Find the lowest value in the unsorted part of the array
        {
            if (array[j] < array[minIndex])
            {
                minIndex = j;
            }
        }

        // 0  1  2  3  4  5  6  7
        // 64 34 25 12 22 11 90 5
        if (minIndex != i)   // Only swap if the next lowest value is not already in its sorted position.
        {
            // Put the next lowest value in its sorted position.
            int minValue = array[minIndex];
            array[minIndex] = array[i];
            array[i] = minValue;
        }
    }

    printf("Sorted array: ");
    PrintArray(array, length);
}

void InsertionSort(void) 
{
    int array[] = {64, 34, 25, 12, 22, 11, 90, 5};
    int length = sizeof(array) / sizeof(array[0]);

    printf("Original array: ");
    PrintArray(array, length);

    for (int i=1; i < length; i++)    // traverse the whole array starting from the second element
    {
        int currentValue = array[i];
        int j = i - 1;

        // Move elements of the sorted portion of the array that are greater than the currentValue to one position ahead of their current position.
        while (j >= 0 && array[j] > currentValue)
        {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = currentValue;   // Insert the currentValue into its correct position in the sorted portion of the array.
    }

    printf("Sorted array: ");
    PrintArray(array, length);
}

/**
 * @brief Partition the array around a pivot and return the pivot's final index.
 * All values less than or equal to the pivot are moved to the left side,
 * and values greater than the pivot are moved to the right side.
 * 
 * @param array The array to be partitioned.
 * @param low The starting index of the subarray to be partitioned.
 * @param high The ending index of the subarray to be partitioned.
 * @return int The final index of the pivot.
 */
static int QuickSort_Partition(int array[], int low, int high) {
    int pivot = array[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        // If the current item is smaller than or equal to the pivot,
        // move it to the left partition by swapping it with the element
        // immediately after the last smaller-or-equal element.
        if (array[j] <= pivot) {
            i++;
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }

    // Place the pivot immediately after the last smaller-or-equal element.
    int temp = array[i + 1];
    array[i + 1] = array[high];
    array[high] = temp;
    return i + 1;
}

/**
 * @brief Recursively sort the subarrays on either side of the pivot.
 * 
 * @param array The array to be sorted.
 * @param low The starting index of the subarray to be sorted.
 * @param high The ending index of the subarray to be sorted.
 */
static void QuickSort_Helper(int array[], int low, int high) {
    if (low < high) {
        int pivotIndex = QuickSort_Partition(array, low, high);

        // Sort the left partition (elements smaller than or equal to the pivot).
        QuickSort_Helper(array, low, pivotIndex - 1);

        // Sort the right partition (elements greater than the pivot).
        QuickSort_Helper(array, pivotIndex + 1, high);
    }
}

void QuickSort(void)
{
    int array[] = {64, 34, 25, 12, 22, 11, 90, 5};
    int length = sizeof(array) / sizeof(array[0]);

    printf("Original array: ");
    PrintArray(array, length);

    // Start QuickSort on the full array. The helper function will recursively
    // partition and sort smaller subarrays until the entire array is sorted.
    QuickSort_Helper(array, 0, length - 1);

    printf("Sorted array: ");
    PrintArray(array, length);
}