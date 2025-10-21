/*
 * game.c
 *
 * Implements the core game logic initialization, cleanup, and input dispatch.
 * Most game mechanics are now delegated to separate files.
 */
#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "color.h"
#include "newSleep.h"

/* Function prototypes for game-related modules (now external) */
void move_player(GameState* game, int new_row, int new_col);
void triggerTrap(GameState* game);
void spreadWater(GameState* game);
void check_game_over(GameState* game);


/**
 * @brief Allocates memory and initializes a new GameState structure.
 * * Loads the map, initializes undo history, and finds player start position.
 *
 * @param map_filename The path to the map file.
 * @return A pointer to the newly created GameState, or NULL on error.
 */
GameState* create_game_state(char* map_filename) {
    GameState* game = (GameState*)malloc(sizeof(GameState));
    if (game != NULL) {
        /* Attempt to load map data from file */
        game->map = loadMap(map_filename);
        if (game->map == NULL) {
            free(game); /* Clean up the GameState struct if map load fails */
            return NULL;
        }
        
        /* Initialize the history linked list for undo feature */
        game->undo_history = create_undo_history();
        
        /* Find and set the initial player position (P) */
        find_char(game->map, 'P', &game->player_row, &game->player_col);
        
        game->trap_triggered = 0; /* Trap is initially not active */
        game->game_over = 0; /* Game status: 0 = ongoing */
        
        /* Save the initial state for the first undo point */
        save_game_state(game->undo_history, game);
    }
    return game;
}

/**
 * @brief Frees all dynamically allocated memory for the GameState.
 * * @param game A pointer to the GameState structure to free.
 */
void free_game_state(GameState* game) {
    if (game != NULL) {
        /* Delegate cleanup to respective modules */
        free_map(game->map);
        free_undo_history(game->undo_history);
        free(game);
    }
}

/**
 * @brief Clears the screen and prints the current map and instructions.
 * * @param game A pointer to the current GameState.
 */
void print_game_state(GameState* game) {
    print_map(game->map);
}

/**
 * @brief Processes a single character input from the user.
 * * Handles movement ('w','s','a','d') and undo ('u').
 *
 * @param game A pointer to the current GameState.
 * @param input The character input from the user.
 */
void process_input(GameState* game, char input) {
    int new_row = game->player_row;
    int new_col = game->player_col;

    /* Ignore input if the game has already ended */
    if (game->game_over != 0) return;

    switch (input) {
        case 'w': new_row--; break;
        case 's': new_row++; break;
        case 'a': new_col--; break;
        case 'd': new_col++; break;
        case 'u': 
            /* Restore previous state and exit the function early */
            restore_game_state(game->undo_history, game); 
            return;
        default: 
            /* Ignore unrecognized input characters */
            return;
    }
    
    /* Call the external movement handler */
    move_player(game, new_row, new_col);
}
