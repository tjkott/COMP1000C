/*
 * linked_list.h
 */

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

/* A node (each element in the linked list) */
typedef struct Node {
    void* data; /* void pointer to hold data for node.*/
    struct Node* next; /* pointer to next node in the list. */
} Node;

/* LinkedList structs represents the entire list.*/
typedef struct {
    Node* head; 
} LinkedList;

/* Define a new type, FreeDataFunc, which represents any function that takes a void pointer
 * as an argument and returns nothing. We use this to allow the
 * linked list to free any kind of data it might be storing.
 */
typedef void (*FreeDataFunc)(void* data);

LinkedList* createLinkedList(void); /* Declared createLinkedList function and returns a pointer to Liinkedlist*/
void freeLinkedList(LinkedList* list, FreeDataFunc free_data);
void insertFirst(LinkedList* list, void* data);
void* removeFirst(LinkedList* list, int* error);

#endif /* LINKED_LIST_H */
