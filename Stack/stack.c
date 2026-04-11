#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include "log.h"

#define STACK_SIZE 5

int stack[STACK_SIZE] = {0};
int top = -1;

static bool IsFull(void);

/**
 * @brief Checks if the stack is full.
 * 
 * @return true if the stack is full, false otherwise.
 */
static bool IsFull(void)
{
    int stackSize = STACK_SIZE - 1;
    if (top == stackSize)
    {
        LOG_ERROR_N("Stack is full! Cannot push new element.");
        return true;
    }
    else
    {
        return false;
    }
}

void Stack_Push(int data)
{
    if(!IsFull())
    {
        stack[++top] = data;
        LOG_INFO_N("Pushed %d onto the stack", data);
    }
    else
    {
        LOG_ERROR_N("Stack overflow! Cannot push %d", data);
    }
}

int Stack_Pop(void)
{
    if (Stack_IsEmpty())
    {
        return -1;
    }

    int poppedValue = stack[top];
    top--;
    LOG_INFO_N("Popped %d from the stack", poppedValue);

    return poppedValue;
}

int Stack_Peek(void)
{
    if (!Stack_IsEmpty())
    {
        int topValue = stack[top];
        LOG_INFO_N("Top element is %d", topValue);
        return topValue;
    }
    else
    {
        LOG_ERROR_N("Stack is empty! Cannot peek.");
        return -1;
    }
}

bool Stack_IsEmpty(void)
{
    if (top == -1)
    {
        LOG_INFO_N("Stack is empty.");
        return true;
    }
    else
    {
        LOG_INFO_N("Stack is not empty.");
        return false;
    }
}