#include "doublyLinkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include "log.h"

typedef struct Node_t   // Using Node_t here prevents a warning when using node = node->next
{
    int data;
    struct Node_t *next;
    struct Node_t *prev;
} Node_t;

static Node_t *myNode = NULL;

static void PrintDoublyLinkedList(Node_t *node);
static Node_t *CreateNode(int data);
static Node_t *FindNode(int position);

/**
 * @brief Prints the entire doubly linked list
 * 
 * @param node The head node of the doubly linked list
 */
static void PrintDoublyLinkedList(Node_t *node)
{
    printf("NULL <-> ");
    while (node != NULL) {
        printf("%d <-> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

/**
 * @brief Finds the node at the specified position in the linked list.
 * 
 * @param position The zero-based index of the node to find
 * @return Node_t* Pointer to the node at the specified position, or NULL if position is out of bounds
 */
static Node_t *FindNode(int position)
{
    int count = 0;
    Node_t *current = myNode;

    while (current != NULL) 
    {
        if (count == position) 
        {
            return current;
        }
        current = current->next;
        count++;
    }

    LOG_ERROR_N("Position %d is out of bounds.", position);
    return NULL;
}

/**
 * @brief Creates a new node with the given data and returns a pointer to the node.
 * 
 * @param data value to be stored in the new node
 * @return Node_t* Pointer to the newly created node, or NULL if creation fails
 */
static Node_t *CreateNode(int data) 
{
    Node_t *newNode = (Node_t *)malloc(sizeof(Node_t));
    if (newNode == NULL)
    {
        LOG_ERROR_N("Failed to create node. Not enough memory.");
        return NULL;
    }

    // Initialize the new node's data and pointers
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;

    return newNode;
}

void DoublyLinkedList_InsertAtHead(int data)
{
    Node_t *newNode = CreateNode(data);
    if (newNode == NULL)
    {
        return;
    }

    if (myNode == NULL)
    {
        myNode = newNode;
        PrintDoublyLinkedList(myNode);
        return;
    }

    myNode->prev = newNode; // Point the current head's prev pointer to the new node
    newNode->next = myNode; // Point to the rest of the existing list. If myNode is NULL, this correctly sets the next pointer to NULL.
    myNode = newNode;

    PrintDoublyLinkedList(myNode);
}

void DoublyLinkedList_InsertAtTail(int data)
{
    Node_t *newNode = CreateNode(data);
    if (newNode == NULL)
    {
        return;
    }

    if (myNode == NULL) 
    {
        myNode = newNode; // If the list is empty, set the new node as the head
        PrintDoublyLinkedList(myNode);
        return;
    }

    // Traverse to the end of the list and append the new node
    Node_t *current = myNode;
    while (current->next != NULL) 
    {
        current = current->next;
    }
    current->next = newNode;
    newNode->prev = current;

    PrintDoublyLinkedList(myNode);
}

void DoublyLinkedList_InsertAtPosition(int data, int position)
{
    Node_t *existingNode = FindNode(position-1);
    if (existingNode == NULL)
    {
        return;
    }

    Node_t *newNode = CreateNode(data);
    if (newNode == NULL)
    {
        return;
    }

    newNode->next = existingNode->next;
    newNode->prev = existingNode;
    existingNode->next = newNode;

    PrintDoublyLinkedList(myNode);
}

void DoublyLinkedList_DeleteHead(void)
{
    if (myNode == NULL) 
    {
        LOG_ERROR_N("Doubly Linked List is already empty.");
        return;
    }

    if (myNode->next == NULL) 
    {
        free(myNode);
        myNode = NULL;
        PrintDoublyLinkedList(myNode);
        return;
    }

    Node_t *temp = myNode;
    myNode = myNode->next; //change where the head of myNode is pointing to.
    myNode->prev = NULL; // Set the new head's prev pointer to NULL since it's now the head of the list.
    free(temp);
    temp = NULL;

    PrintDoublyLinkedList(myNode);
}

void DoublyLinkedList_DeleteTail(void)
{
    if (myNode == NULL) 
    {
        LOG_ERROR_N("Doubly Linked List is already empty.");
        return;
    }

    if (myNode->next == NULL) 
    {
        free(myNode);
        myNode = NULL;
        PrintDoublyLinkedList(myNode);
        return;
    }

    Node_t *temp = myNode;
    while (temp->next->next != NULL) // Traverse to the second-to-last node
    {
        temp = temp->next;
    }
    free(temp->next);   // Next node is the last node which needs to be deleted
    temp->next = NULL;

    PrintDoublyLinkedList(myNode);
}

void DoublyLinkedList_DeleteAtPosition(int position)
{
    if (myNode == NULL) 
    {
        LOG_ERROR_N("Doubly Linked List is already empty.");
        return;
    }

    if (position == 0) 
    {
        DoublyLinkedList_DeleteHead();
        return;
    }

    Node_t *previousNode = FindNode(position - 1);
    if (previousNode == NULL || previousNode->next == NULL) 
    {
        LOG_ERROR_N("Position %d is out of bounds.", position);
        return;
    }

    Node_t *temp = previousNode->next;
    previousNode->next = temp->next;
    temp->prev = previousNode;
    free(temp);
    temp = NULL;

    PrintDoublyLinkedList(myNode);
}

void DoublyLinkedList_DeleteList(void)
{
    int count = 0;
    while (myNode != NULL) 
    {
        Node_t *temp = myNode; // Store the current node in a temporary variable
        LOG_INFO_N("Deleting node %d with data: %d", count, myNode->data);
        myNode = myNode->next;
        free(temp); // Free the memory of the current node
        temp = NULL; // Set the temporary pointer to NULL after freeing
        count++;
    }
}