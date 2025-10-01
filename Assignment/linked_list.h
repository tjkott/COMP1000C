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

/* The linked list structure */
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
LinkedList* create_linked_list(void);
void free_linked_list(LinkedList* list, FreeDataFunc free_data);
void insert_first(LinkedList* list, void* data);
void* remove_first(LinkedList* list, int* error);

#endif /* LINKED_LIST_H */