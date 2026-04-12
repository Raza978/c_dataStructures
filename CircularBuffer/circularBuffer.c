#include "circularBuffer.h"
#include <stdio.h>
#include <stdlib.h>
#include "log.h"

#define CIRCULAR_BUFFER_SIZE 5

int circularBuffer[CIRCULAR_BUFFER_SIZE] = {0};
int writeIndex = 0;     // Tracks the tail of the buffer (where the next element will be written)
int readIndex = 0;      // Tracks the head of the buffer (where the next element will be read)

static bool CircularBuffer_IsFull(void);

/**
 * @brief Checks if the circular buffer is full.
 * 
 * @return true if the circular buffer is full, false otherwise.
 */
static bool CircularBuffer_IsFull(void)
{
    // 0 1 2 3 4 5 // CIRCULAR_BUFFER_SIZE = 5
    // 0 1 2 3 4   // indexes of circular buffer
    // R       W   // If the next write index is equal to the read index, then the buffer is full.
    int nextWriteIndex = (writeIndex + 1) % CIRCULAR_BUFFER_SIZE;
    if (nextWriteIndex == readIndex)
    {
        LOG_ERROR_N("Circular buffer is full! Cannot push new data to the buffer.");
        return true;
    }
    else
    {
        return false;
    }
}

void CircularBuffer_Push(int data)
{
    if(!CircularBuffer_IsFull())
    {
        circularBuffer[writeIndex] = data;
        LOG_INFO_N("Pushed %d onto the circular buffer[%d]", data, writeIndex);
        writeIndex = (writeIndex + 1) % CIRCULAR_BUFFER_SIZE; // % operator wraps the index back to 0 when it reaches the end of the buffer
    }
    else
    {
        LOG_ERROR_N("Circular buffer is full! Cannot push %d at index %d", data, writeIndex);
    }
}

int CircularBuffer_Pop(void)
{
    if (writeIndex == readIndex) // If the write index is equal to the read index, then the buffer is empty.
    {
        LOG_ERROR_N("Circular buffer is empty! Cannot pop from the buffer.");
        return -1;
    }

    int poppedValue = circularBuffer[readIndex];
    LOG_INFO_N("Popped %d from the circular buffer[%d]", poppedValue, readIndex);
    readIndex = (readIndex + 1) % CIRCULAR_BUFFER_SIZE; // % operator wraps the index back to 0 when it reaches the end of the buffer

    return poppedValue;
}
