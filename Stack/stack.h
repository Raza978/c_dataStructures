#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

/**
 * @brief Pushes an element onto the stack.
 * 
 * @param data The integer data to be pushed onto the stack.
 */
void Stack_Push(int data);

/**
 * @brief Pops an element from the stack.
 * 
 * @return The integer data popped from the stack, or -1 if the stack is empty.
 */
int Stack_Pop(void);

/**
 * @brief Peeks at the top element of the stack.
 * 
 * @return The integer data at the top of the stack, or -1 if the stack is empty.
 */
int Stack_Peek(void);

/**
 * @brief Checks if the stack is empty.
 * 
 * @return true if the stack is empty, false otherwise.
 */
bool Stack_IsEmpty(void);

#endif //STACK_H