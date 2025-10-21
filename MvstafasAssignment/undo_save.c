/*
 * undo.c
 *
 * Implements the core logic for the UndoHistory structure and its helper functions.
 * Saving and restoring logic is now external.
 */

#include <stdlib.h>
#include <stdio.h>
#include "undo.h"
#include "game.h" 
#include "map.h" /* For freeing Map in free_undo_state */

/* Externally defined functions for memory cleanup */
void free_map(Map* map);

/**
 * @brief Helper function to free an UndoState structure and its internal map snapshot.
 * * This function is used as the FreeDataFunc in freeLinkedList.
 *
 * @param data A void pointer to the UndoState to be freed.
 */
static void free_undo_state(void* data) {
    UndoState* state = (UndoState*)data;
    if (state != NULL) {
        /* Free the map snapshot stored within the state */
        free_map(state->map_snapshot);
        free(state); /* Free the UndoState struct itself */
    }
}

/**
 * @brief Creates and initializes a new UndoHistory structure.
 * * @return A pointer to the new UndoHistory, or NULL on failure.
 */
UndoHistory* create_undo_history(void) {
    UndoHistory* history = (UndoHistory*)malloc(sizeof(UndoHistory));
    if (history != NULL) {
        /* Initialize the underlying linked list */
        history->history_list = createLinkedList();
    }
    return history;
}

/**
 * @brief Frees all memory associated with the UndoHistory, including all saved states.
 * * @param history A pointer to the UndoHistory to free.
 */
void free_undo_history(UndoHistory* history) {
    if (history != NULL) {
        /* Use the linked list's specialized free function with our custom data free function */
        freeLinkedList(history->history_list, free_undo_state);
        free(history);
    }
}
