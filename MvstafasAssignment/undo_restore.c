/*
 * undo_restore.c
 *
 * Implements the function to revert the game state to the previous snapshot.
 */
#include <stdlib.h>
#include "undo.h"
#include "game.h" 
#include "map.h" /* For map utilities and memory */

/* Externally defined functions for map utilities and memory */
char** copy_map_data_from_source(Map* source_map);
void free_map_grid(char** grid, int rows);
void* removeFirst(LinkedList* list, int* error);
static void free_undo_state(void* data); /* Need prototype for cleanup */


/**
 * @brief Restores the game state to the one saved before the last player move.
 * * Removes the most recent snapshot, and restores from the new 'head' of the list.
 * * @param history The UndoHistory list to restore from.
 * @param current_state The current GameState to overwrite.
 */
void restore_game_state(UndoHistory* history, struct GameState* current_state) {
    UndoState* last_state; /* Pointer to the state we are restoring FROM */

    /* Check if there are at least two states: the current (to remove) and the previous (to restore) */
    if (history->history_list->head != NULL && history->history_list->head->next != NULL) {
        
        /* 1. Remove and free the very last state saved (the current move's snapshot) */
        free_undo_state(removeFirst(history->history_list, NULL));

        /* 2. The new head of the list is the state we want to restore to */
        last_state = (UndoState*)history->history_list->head->data;

        /* 3. Restore simple data fields */
        current_state->player_row = last_state->player_row;
        current_state->player_col = last_state->player_col;
        current_state->trap_triggered = last_state->trap_triggered;
        
        /* 4. Free the current map grid data */
        free_map_grid(current_state->map->grid, current_state->map->rows + 2);
        
        /* 5. Create a deep copy of the map grid from the snapshot and assign it */
        current_state->map->grid = copy_map_data_from_source(last_state->map_snapshot);
    }
}
