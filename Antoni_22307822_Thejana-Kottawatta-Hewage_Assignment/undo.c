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

UndoHistory* create_undo_history(void) {
    UndoHistory* history = (UndoHistory*)malloc(sizeof(UndoHistory));
    if (history != NULL) {
        history->history_list = createLinkedList();
    }
    return history;
}

void free_undo_history(UndoHistory* history) {
    if (history != NULL) {
        freeLinkedList(history->history_list, free_undo_state);
        free(history);
    }
}

void save_game_state(UndoHistory* history, struct GameState* current_state) {
    UndoState* snapshot = (UndoState*)malloc(sizeof(UndoState));
    if (snapshot == NULL) return;

    snapshot->map_snapshot = (Map*)malloc(sizeof(Map));
    if (snapshot->map_snapshot == NULL) {
        free(snapshot);
        return;
    }
    
    snapshot->map_snapshot->rows = current_state->map->rows;
    snapshot->map_snapshot->cols = current_state->map->cols;
    snapshot->map_snapshot->grid = copy_map_data_from_source(current_state->map);

    if (snapshot->map_snapshot->grid == NULL) {
        free(snapshot->map_snapshot);
        free(snapshot);
        return;
    }

    snapshot->player_row = current_state->player_row;
    snapshot->player_col = current_state->player_col;
    snapshot->trap_triggered = current_state->trap_triggered;

    insertFirst(history->history_list, snapshot);
}

void restore_game_state(UndoHistory* history, struct GameState* current_state) {
    UndoState* last_state;

    if (history->history_list->head != NULL && history->history_list->head->next != NULL) {
        free_undo_state(removeFirst(history->history_list, NULL));
        last_state = (UndoState*)history->history_list->head->data;
        current_state->player_row = last_state->player_row;
        current_state->player_col = last_state->player_col;
        current_state->trap_triggered = last_state->trap_triggered;
        free_map_grid(current_state->map->grid, current_state->map->rows + 2);
        current_state->map->grid = copy_map_data_from_source(last_state->map_snapshot);
    }
}
