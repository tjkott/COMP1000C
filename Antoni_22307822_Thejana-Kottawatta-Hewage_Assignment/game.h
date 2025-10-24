/*
 * game.h 
 * Defines the GameState struct and functions for managing the game.
 */

#ifndef GAME_H
#define GAME_H

#include "map.h"
#include "undo.h"
#include "linked_list.h"

/* The main struct to hold all information about the current game state */
typedef struct GameState {
    Map* map;
    int player_row;
    int player_col;
    int trap_triggered;
    int game_over; /* 0 = ongoing, 1 = win, -1 = lose */
    UndoHistory* undo_history;
} GameState;

/* Function prototypes for game operations */
GameState* create_game_state(char* map_filename);
void free_game_state(GameState* game);
void print_game_state(GameState* game);
void process_input(GameState* game, char input);

#endif /* GAME_H */
