/*
 * undo.h
 *
 * Header file for the undo functionality.
 * Manages the history of game states using a linked list.
 */
#ifndef UNDO_H
#define UNDO_H

#include "map.h"
#include "linked_list.h"

/* Forward declaration to break the circular dependency with game.h */
struct GameState;

/* A struct to hold a snapshot of the game state for one turn */
typedef struct {
    Map* map_snapshot;
    int player_row;
    int player_col;
    int trap_triggered;
} UndoState;

/* A wrapper for the linked list to represent the history */
typedef struct UndoHistory {
    LinkedList* history_list;
} UndoHistory;

/* Function prototypes for managing undo history */
UndoHistory* create_undo_history(void);
void free_undo_history(UndoHistory* history);
void save_game_state(UndoHistory* history, struct GameState* current_state);
void restore_game_state(UndoHistory* history, struct GameState* current_state);

#endif /* UNDO_H */
