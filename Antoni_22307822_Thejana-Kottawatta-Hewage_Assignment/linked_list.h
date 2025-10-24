/*
 * linked_list.h
 * Header file for a generic linked list implementation.
 */

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h> /* Needed for NULL definition */

/* A node in the linked list */
typedef struct Node {
    void* data;
    struct Node* next;
} Node;

/* The linked list structure */
typedef struct {
    Node* head;
} LinkedList;

/* Typedef for a function pointer used to free data stored in the list */
typedef void (*FreeDataFunc)(void* data);

/* Function prototypes for linked list operations */
LinkedList* create_linked_list(void);
void free_linked_list(LinkedList* list, FreeDataFunc free_data);
void insert_first(LinkedList* list, void* data);
void* remove_first(LinkedList* list, int* error);

#endif /* LINKED_LIST_H */
