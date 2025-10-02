/*
 * linked_list.c
 *
 * Implements a generic singly linked list.
 */

#include <stdlib.h>
#include "linked_list.h"

/*
 * Creates and returns a new empty linked list.
 */
LinkedList* create_linked_list(void) {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    if (list != NULL) {
        list->head = NULL;
    }
    return list;
}

/*
 * Frees all memory associated with a linked list, including its nodes and data.
 */
void free_linked_list(LinkedList* list, FreeDataFunc free_data) {
    Node* current;
    Node* next;

    if (list != NULL) {
        current = list->head;
        while (current != NULL) {
            next = current->next;
            if (free_data != NULL) {
                free_data(current->data);
            }
            free(current);
            current = next;
        }
        free(list);
    }
}

/*
 * Inserts a new node at the beginning of the list.
 */
void insert_first(LinkedList* list, void* data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node != NULL) {
        new_node->data = data;
        new_node->next = list->head;
        list->head = new_node;
    }
}

/*
 * Removes and returns the data from the first node of the list.
 */
void* remove_first(LinkedList* list, int* error) {
    void* data = NULL;
    Node* temp;

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
