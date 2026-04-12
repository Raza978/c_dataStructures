#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

#include <stdbool.h>

/**
 * @brief Pushes an element onto the circular buffer.
 * 
 * @param data The integer data to be pushed onto the circular buffer.
 */
void CircularBuffer_Push(int data);

/**
 * @brief Pops (reads) an element from the circular buffer.
 * 
 * @return The integer data popped from the circular buffer, or -1 if the circular buffer is empty.
 */
int CircularBuffer_Pop(void);

#endif //CIRCULARBUFFER_H