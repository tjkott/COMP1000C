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
void free_undo_state(void* data) {
    UndoState* state = (UndoState*)data;
    if (state != NULL) {
        free_map(state->map_snapshot);
        free(state);
    }
}

/*
 * Creates and initializes an UndoHistory object.
 */
UndoHistory* create_undo_history(void) {
    UndoHistory* history = (UndoHistory*)malloc(sizeof(UndoHistory));
    if (history != NULL) {
        history->history_list = create_linked_list();
    }
    return history;
}

/*
 * Frees all memory associated with the undo history.
 */
void free_undo_history(UndoHistory* history) {
    if (history != NULL) {
        /* free_undo_state is passed as a function pointer to free the data in each node */
        free_linked_list(history->history_list, free_undo_state);
        free(history);
    }
}

/*
 * Saves a snapshot of the current game state to the history.
 */
void save_game_state(UndoHistory* history, struct GameState* current_state) {
    UndoState* snapshot = (UndoState*)malloc(sizeof(UndoState));
    if (snapshot == NULL) {
        return; /* Failed to save state */
    }

    /* Create a deep copy of the map */
    snapshot->map_snapshot = (Map*)malloc(sizeof(Map));
    if(snapshot->map_snapshot != NULL)
    {
        snapshot->map_snapshot->rows = current_state->map->rows;
        snapshot->map_snapshot->cols = current_state->map->cols;
        snapshot->map_snapshot->grid = copy_map_data_from_source(current_state->map);

        if (snapshot->map_snapshot->grid != NULL)
        {
            /* Copy player position and trap status */
            snapshot->player_row = current_state->player_row;
            snapshot->player_col = current_state->player_col;
            snapshot->trap_triggered = current_state->trap_triggered;

            insert_first(history->history_list, snapshot);
        }
        else
        {
            free(snapshot->map_snapshot); /* Clean up if grid copy fails */
            free(snapshot);
        }
    }
    else
    {
        free(snapshot); /* Clean up if map snapshot allocation fails */
    }
}

/*
 * Restores the game state to the previously saved state.
 */
void restore_game_state(UndoHistory* history, struct GameState* current_state) {
    UndoState* last_state;

    /* Check if there is a previous state to restore (list must have current and a previous state) */
    if (history->history_list->head != NULL && history->history_list->head->next != NULL) {
        /* The current state is the head, so we remove it to get to the previous one */
        free_undo_state(remove_first(history->history_list, NULL));

        /* The new head is the state we want to restore */
        last_state = (UndoState*)history->history_list->head->data;

        /* Restore player position and trap status */
        current_state->player_row = last_state->player_row;
        current_state->player_col = last_state->player_col;
        current_state->trap_triggered = last_state->trap_triggered;

        /* Free the current map grid */
        free_map_grid(current_state->map->grid, current_state->map->rows + 2);
        
        /* Replace it with a copy of the restored map grid */
        current_state->map->grid = copy_map_data_from_source(last_state->map_snapshot);
    }
}


