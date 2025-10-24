/*
 * undo.c
 *
 * Implements the undo feature by saving and restoring game states.
 */

#include <stdlib.h>
#include <stdio.h>
#include "undo.h"
#include "game.h" /* Required for the full definition of GameState */

/* Private helper function to free an UndoState struct */
static void free_undo_state(void* data) {
    UndoState* state = (UndoState*)data;
    if (state != NULL) {
        free_map(state->map_snapshot);
        free(state);
    }
}

/*
 * Initialises UndoHistory object.
 * Returns a pointer to the new object, or NULL on failure.
 */
UndoHistory* create_undo_history(void) { 
    UndoHistory* history = (UndoHistory*)malloc(sizeof(UndoHistory));
    if (history != NULL) {
        history->history_list = create_linked_list(); 
        /* If linked list creation fails, free the history struct */
        if (history->history_list == NULL) {
            free(history);
            history = NULL;
        }
    }
    /* Single return statement */
    return history;
}

/*
 * Frees all memory associated with the undo history.
 */
void free_undo_history(UndoHistory* history) { 
    if (history != NULL) {
        free_linked_list(history->history_list, free_undo_state); 
        free(history);
    }
}

/*
 * Saves a snapshot of the current game state to the history.
 */
void save_game_state(UndoHistory* history, struct GameState* current_state) { 
    UndoState* snapshot = NULL;
    Map* map_copy = NULL;
    char** grid_copy = NULL;
    int success = 0; /* Status flag */
    /* Allocate snapshot struct */
    snapshot = (UndoState*)malloc(sizeof(UndoState));
    if (snapshot != NULL) {
        /* Allocate map struct within snapshot */
        map_copy = (Map*)malloc(sizeof(Map));
        if (map_copy != NULL) {
            /* Copy map dimensions */
            map_copy->rows = current_state->map->rows;
            map_copy->cols = current_state->map->cols;
            /* Copy the grid data */
            grid_copy = copy_map_data_from_source(current_state->map);
            if (grid_copy != NULL) {
                /* Assign copied grid to snapshot map */
                map_copy->grid = grid_copy;
                snapshot->map_snapshot = map_copy;
                /* Copy player position and trap status */
                snapshot->player_row = current_state->player_row;
                snapshot->player_col = current_state->player_col;
                snapshot->trap_triggered = current_state->trap_triggered;
                insert_first(history->history_list, snapshot); /* Insert the snapshot into the history */
                success = 1; /* i. e. successful */
            } else {
                free(map_copy);
            }
        }
    }
    if (!success && snapshot != NULL) {
        free(snapshot);
    }

}

/*
 * Restores the game state to the previously saved state. (undo)
 */
void restore_game_state(UndoHistory* history, struct GameState* current_state) { 
    UndoState* last_state = NULL;
    int error_flag = 0; /* To check remove_first result */
    void* removed_data = NULL;
    char** restored_grid_copy = NULL; /* Pointer for the copied grid */

    /* Check if there is a previous state to restore */
    if (history->history_list->head != NULL && history->history_list->head->next != NULL) {
        /* Remove the *current* state from the list */
        removed_data = remove_first(history->history_list, &error_flag); 
        if (!error_flag && removed_data != NULL) {
             /* Free the state we just removed */
            free_undo_state(removed_data);

            /* The new head is the state we want to restore */
            if (history->history_list->head != NULL) {
                 last_state = (UndoState*)history->history_list->head->data;

                /* Create a new copy of the restored grid *before* freeing the old one */
                restored_grid_copy = copy_map_data_from_source(last_state->map_snapshot);

                if (restored_grid_copy != NULL) {
                    current_state->player_row = last_state->player_row;
                    current_state->player_col = last_state->player_col;
                    current_state->trap_triggered = last_state->trap_triggered;
                    free_map_grid(current_state->map->grid, current_state->map->rows + 2); 
                    current_state->map->grid = restored_grid_copy; /* Assign the newly copied grid to the current state */
                    /* Update map dimensions */
                    current_state->map->rows = last_state->map_snapshot->rows;
                    current_state->map->cols = last_state->map_snapshot->cols;
                }
            }
        }
    }
}
