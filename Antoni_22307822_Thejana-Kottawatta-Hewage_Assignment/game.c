/*
 * game.c
 *
 * Implements the core game logic, including state management,
 * player movement, trap handling, and the flood-fill algorithm.
 */
#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "color.h"
#include "newSleep.h"

static void move_player(GameState* game, int new_row, int new_col);
static void trigger_trap(GameState* game);
static void spread_water(GameState* game);
static void check_game_over(GameState* game);

/*
 * Initialises the main GameState struct.
 * Returns a pointer to the new GameState, or NULL on failure.
 */
GameState* create_game_state(char* map_filename) {
    GameState* game = NULL;
    int success = 0; /* Status flag */

    game = (GameState*)malloc(sizeof(GameState)); /* Allocate memory for the GameState struct */
    if (game != NULL) {
        /* Load the map */
        game->map = load_map(map_filename); 
        if (game->map != NULL) {
            /* Create the undo history */
            game->undo_history = create_undo_history(); 
            if (game->undo_history != NULL) {
                find_char(game->map, 'P', &game->player_row, &game->player_col); 
                game->game_over = 0;
                save_game_state(game->undo_history, game);
                success = 1; /* i.e. successful */
            } else {
                free_map(game->map);
            }
        }
    }    
    if (!success && game != NULL) { /* if failed: free memory*/
        free(game);
        game = NULL;
    }
    return game; /* signgle return statement according to conding standards*/
}

void free_game_state(GameState* game) {
    if (game != NULL) {
        free_map(game->map);
        free_undo_history(game->undo_history);
    }
}

/*
 * Prints the current state of the game to the terminal.
 */
void print_game_state(GameState* game) {
    print_map(game->map);
}

/*
 * Processes a single character of user input to update the game state.
 */
void process_input(GameState* game, char input) {
    int new_row = game->player_row;
    int new_col = game->player_col;
    int perform_move = 0; /* Flag to indicate if a move should be attempted */

    if (game->game_over == 0) {
        switch (input) {
            case 'w':
                new_row--;
                perform_move = 1;
                break; /* break allowed on switch case*/
            case 's':
                new_row++;
                perform_move = 1;
                break;
            case 'a':
                new_col--;
                perform_move = 1;
                break;
            case 'd':
                new_col++;
                perform_move = 1;
                break;
            case 'u':
                restore_game_state(game->undo_history, game);
                break;
            default:
                break;
        }
        if (perform_move) {
            move_player(game, new_row, new_col);
        }
    }
}

/*
 * Moves the player to a new position if the move is valid.
 */
static void move_player(GameState* game, int new_row, int new_col) {
    char target_char = game->map->grid[new_row][new_col];
    if (target_char != '*' && target_char != 'O' && target_char != 'X') { /* Check if the target cell is walkable */
        game->map->grid[game->player_row][game->player_col] = ' '; /* Clear the player's old position */
        game->player_row = new_row; /* Update player coordinates */
        game->player_col = new_col;
        check_game_over(game); /* Check for win/lose/trap conditions at the new location */
        /* Only update map and proceed if game is not over */
        if(game->game_over == 0) {
            game->map->grid[game->player_row][game->player_col] = 'P'; /* Place player character on the new position */
            /* If the trap has been triggered, spread water */
            if (game->trap_triggered == 1) {
                spread_water(game);
                check_game_over(game);
            }
        }
        if (game->game_over == 0) {
            save_game_state(game->undo_history, game);
    }
    }
}

/*
 * Check player's position to see if player lost the game. 
 */
static void check_game_over(GameState* game) {
    char current_pos_char = game->map->grid[game->player_row][game->player_col];
    int goal_row, goal_col;

    find_char(game->map, 'G', &goal_row, &goal_col);
    /* Check win condition */
    if (game->player_row == goal_row && game->player_col == goal_col) {
        game->game_over = 1; /* 1 = Win */
        print_map(game->map); 
        setForeground("green");
        printf("\nYou win!\n");
        setForeground("reset");
        newSleep(2.0f);
    }
    /* Check lose condition */
    else if (current_pos_char == '!') {
        game->game_over = -1; /* Lose */
        game->map->grid[game->player_row][game->player_col] = '!'; /* Ensure player is submerged */
        print_map(game->map);
        setForeground("red");
        printf("\nYou lose!\n");
        setForeground("reset");
        newSleep(2.0f);
    }
    /* Check for trap activation (only if game not already over) */
    else if (current_pos_char == '@') {
        trigger_trap(game); 
    }
}
/*
 * Activates the trap, removing it and all trapdoors.
 */
static void trigger_trap(GameState* game) {
    game->trap_triggered = 1;
    replace_char(game->map, '@', ' '); 
    replace_char(game->map, 'X', ' '); 
}

/*
 * Spreads water one block in each of 4 cardinal direction usin flood-fill approach.
 */
static void spread_water(GameState* game) {
    int i, j;
    char** temp_grid = NULL;
    temp_grid = copy_map_data_from_source(game->map);
    if(temp_grid != NULL)
    {
        /* Iterate through the map to find existing water cells */
        for (i = 1; i < game->map->rows + 1; i++) {
            for (j = 1; j < game->map->cols + 1; j++) {
                /* If the current cell in the *original* grid has water */
                if (game->map->grid[i][j] == '!') {
                    /* Check adjacent cells in the *original* grid, update *temp* grid */
                    if (game->map->grid[i-1][j] == ' ') temp_grid[i-1][j] = '!';
                    if (game->map->grid[i+1][j] == ' ') temp_grid[i+1][j] = '!';
                    if (game->map->grid[i][j-1] == ' ') temp_grid[i][j-1] = '!';
                    if (game->map->grid[i][j+1] == ' ') temp_grid[i][j+1] = '!';
                }
            }
        }
        free_map_grid(game->map->grid, game->map->rows + 2); /* Free the old grid and replace it with the updated one */
        game->map->grid = temp_grid;
    }
}
