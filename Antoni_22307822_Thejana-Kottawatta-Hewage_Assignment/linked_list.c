/*
 * linked_list.c
 * Singly linked list for the game. 
 */

#include <stdlib.h>
#include "linked_list.h"

/*
 * Creates and returns a new empty linked list.
 */
LinkedList* createLinkedList(void) {
    /* For one LinkedList struct, allocate memory on the heap.*/
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    
    /* Safety check if malloc was sucessful.*/
    if (list != NULL) {
        list->head = NULL;
    }
    return list; 
}

/*
 * Frees all memory associated with a linked list, including its nodes and data.
 */
void freeLinkedList(LinkedList* list, FreeDataFunc free_data) {
    Node* current; /* Pointer to a node.*/
    Node* next; /* Stores the next node before current node is freed.*/
    
    /* Safety check to see if pointer isn't NULL*/
    if (list != NULL) { 
        current = list->head;

        /* Iterate till end of line.*/
        while (current != NULL) {
            next = current->next; 

            /* Safety check to see if func pointer for freeing data isn't NULL.*/
            if (free_data != NULL) {
                free_data(current->data);
            }
            free(current); 
            current = next;
        }
        free(list); /* Free the LinkedList structure itself. */
    }
}

/*
 * Inserts a new node at the beginning of the list.
 */
void insertFirst(LinkedList* list, void* data) {
    
    Node* newnode = (Node*)malloc(sizeof(Node)); /* Allocate memory for new node*/
    
    /* Safety check if malloc was successful*/
    if (newnode != NULL) {
        newnode->data = data;
        newnode->next = list->head;
        list->head = newnode;
    }
}

/*
 * Removes and returns the data from the first node of the list.
 */
void* removeFirst(LinkedList* list, int* error) {
    void* data = NULL; /* void pointer to hold the data from removed node. */
    Node* temp; /* void pointer to hold node being removed. */

    if (list != NULL && list->head != NULL) {
        temp = list->head;
        data = temp->data;
        list->head = temp->next;
        free(temp);
        if (error != NULL) {
            *error = 0;
        }
    } else {
        if (error != NULL) {
            *error = 1; /* List is empty */
        }
    }
    return data;
}
