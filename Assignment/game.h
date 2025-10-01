/*
 * game.h
 *
 * Header file for the main game logic.
 * Defines the GameState struct and declares functions for managing the game.
 */

#ifndef GAME_H
#define GAME_H

#include "map.h"
#include "undo.h"

/* Main struct to hold all information about the current game state */
typedef struct GameState {
    Map* map;
    UndoHistory* history;
    int player_row;
    int player_col;
    int game_over; /* 0 = ongoing, 1 = win, -1 = lose */
    int trap_triggered;
} GameState;

/* Function prototypes for game management */
GameState* create_game_state(char* map_filename);
void free_game_state(GameState* game);
void print_game_state(GameState* game);
void process_input(GameState* game, char input);
void free_map_grid(char** grid, int rows);

#endif /* GAME_H */

