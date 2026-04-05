#ifndef LINKEDLIST_H
#define LINKEDLIST_H

/**
 * @brief Inserts a new node at the head of the linked list.
 * 
 * @param data The integer data to be stored in the new node.
 */
void LinkedList_InsertAtHead(int data);

/**
 * @brief Inserts a new node at the tail of the linked list.
 * 
 * @param data The integer data to be stored in the new node.
 */
void LinkedList_InsertAtTail(int data);

/**
 * @brief Inserts a new node at the specified position in the linked list.
 * 
 * @param data The integer data to be stored in the new node.
 * @param position The zero-based index at which the new node should be inserted.
 */
void LinkedList_InsertAtPosition(int data, int position);

/**
 * @brief Deletes the first node in the linked list.
 * 
 */
void LinkedList_DeleteHead(void);

/**
 * @brief Deletes the last node in the linked list.
 * 
 */
void LinkedList_DeleteTail(void);

/**
 * @brief Deletes the node at the specified position in the linked list.
 * 
 * @param position The zero-based index of the node to be deleted.
 */
void LinkedList_DeleteAtPosition(int position);

/**
 * @brief Deletes all nodes in the linked list.
 * 
 */
void LinkedList_DeleteList(void);

#endif //LINKEDLIST_H