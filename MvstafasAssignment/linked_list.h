/*
 * linked_list.h
 *
 * Header file for a generic linked list implementation.
 */

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

/* A node in the linked list */
typedef struct Node {
    void* data;
    struct Node* next;
} Node;

/* The cast (LinkedList*) is used to convert the generic void* pointer* 
returned by malloc into a pointer of the correct type. */
typedef struct {
    Node* head;
} LinkedList;

/*
 * This is a typedef for a function pointer. It defines a new type,
 * FreeDataFunc, which represents any function that takes a void pointer
 * as an argument and returns nothing. We use this to allow the
 * linked list to free any kind of data it might be storing.
 */
typedef void (*FreeDataFunc)(void* data);

/* Function prototypes for linked list operations */
LinkedList* createLinkedList(void);
void freeLinkedList(LinkedList* list, FreeDataFunc free_data);
void insertFirst(LinkedList* list, void* data);
void* removeFirst(LinkedList* list, int* error);

#endif /* LINKED_LIST_H */
