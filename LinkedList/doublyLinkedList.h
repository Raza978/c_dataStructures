#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

/**
 * @brief Inserts a new node at the head of the doubly linked list.
 * 
 * @param data The integer data to be stored in the new node.
 */
void DoublyLinkedList_InsertAtHead(int data);

/**
 * @brief Inserts a new node at the tail of the doubly linked list.
 * 
 * @param data The integer data to be stored in the new node.
 */
void DoublyLinkedList_InsertAtTail(int data);

/**
 * @brief Inserts a new node at the specified position in the doubly linked list.
 * 
 * @param data The integer data to be stored in the new node.
 * @param position The zero-based index at which the new node should be inserted.
 */
void DoublyLinkedList_InsertAtPosition(int data, int position);

/**
 * @brief Deletes the first node in the doubly linked list.
 * 
 */
void DoublyLinkedList_DeleteHead(void);

/**
 * @brief Deletes the last node in the doubly linked list.
 * 
 */
void DoublyLinkedList_DeleteTail(void);

/**
 * @brief Deletes the node at the specified position in the doubly linked list.
 * 
 * @param position The zero-based index of the node to be deleted.
 */
void DoublyLinkedList_DeleteAtPosition(int position);

/**
 * @brief Deletes all nodes in the doubly linked list.
 * 
 */
void DoublyLinkedList_DeleteList(void);

#endif //DOUBLYLINKEDLIST_H