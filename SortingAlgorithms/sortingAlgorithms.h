#ifndef SORTINGALGORITHMS_H
#define SORTINGALGORITHMS_H

/**
 * @brief Sorts an array of integers in ascending order using the bubble sort algorithm. O(n^2)
 * 
 * @note Repeatedly compares adjacent elements and swaps them if they are 
 * in the wrong order. Each itteration the algorithm puts the largest unsorted 
 * element in its sorted position at the end of the array.
 */
void BubbleSort(void);

/**
 * @brief Sorts an array of integers in ascending order using the selection sort algorithm. O(n^2)
 * 
 * @note Repeatedly finds the minimum element from the unsorted part 
 * and puts it at the beginning of the sorted part.
 */
void SelectionSort(void);

/**
 * @brief Sorts an array of integers in ascending order using the insertion sort algorithm. O(n^2)
 * 
 * @note Builds the final sorted array one item at a time by repeatedly taking the next element 
 * and inserting it into its correct position within the already sorted portion.
 */
void InsertionSort(void);

/**
 * @brief Sorts an array of integers in ascending order using the quick sort algorithm. O(n log n)
 * 
 * @note Uses a divide-and-conquer approach to sort the array by selecting a 'pivot' element
 * and partitioning the array around the pivot. Unsorted elements are moved left or right of the pivot 
 * depending on whether they are less than or greater than the pivot.
 */
void QuickSort(void);

#endif //SORTINGALGORITHMS_H