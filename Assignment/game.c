/*
 * game.c
 *
 * Implements the core game logic, including state management,
 * player movement, trap handling, and the flood-fill algorithm.
 */
#include <stdio.h>
#include <stdlib.h>
#include "game.h"

/* Private helper function prototypes */
static void move_player(GameState* game, int new_row, int new_col);
static void trigger_trap(GameState* game);
static void spread_water(GameState* game);
static void check_game_over(GameState* game);

/*
 * Creates and initializes the main GameState struct.
 */
GameState* create_game_state(char* map_filename) {
    GameState* game = (GameState*)malloc(sizeof(GameState));
    if (game != NULL) {
        game->map = load_map(map_filename);
        if (game->map == NULL) {
            free(game);
            return NULL;
        }
        game->undo_history = create_undo_history();
        find_char(game->map, 'P', &game->player_row, &game->player_col);
        game->trap_triggered = 0;
        game->game_over = 0;
        
        /* Save the initial state for undo */
        save_game_state(game->undo_history, game);
    }
    return game;
}

/*
 * Frees all memory associated with the GameState.
 */
void free_game_state(GameState* game) {
    if (game != NULL) {
        free_map(game->map);
        free_undo_history(game->undo_history);
        free(game);
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

    switch (input) {
        case 'w': new_row--; break;
        case 's': new_row++; break;
        case 'a': new_col--; break;
        case 'd': new_col++; break;
        case 'u':
            restore_game_state(game->undo_history, game);
            return; /* Don't perform move logic after undo */
        default:
            return; /* Ignore invalid keys */
    }
    move_player(game, new_row, new_col);
}

/* --- Private Helper Functions --- */

/*
 * Moves the player to a new position if the move is valid.
 */
static void move_player(GameState* game, int new_row, int new_col) {
    char target_char = game->map->grid[new_row][new_col];

    if (target_char != '*' && target_char != 'O' && target_char != 'X') {
        /* Update player position on the map */
        game->map->grid[game->player_row][game->player_col] = ' ';
        game->player_row = new_row;
        game->player_col = new_col;
        game->map->grid[game->player_row][game->player_col] = 'P';

        if (game->trap_triggered == 1) {
            spread_water(game);
        }

        check_game_over(game);
        
        /* Save state only after a valid move and if the game isn't over */
        if (game->game_over == 0)
        {
            save_game_state(game->undo_history, game);
        }
    }
}

/*
 * Checks the player's current position to see if the game has ended.
 */
static void check_game_over(GameState* game) {
    char current_pos_char = game->map->grid[game->player_row][game->player_col];
    int goal_row, goal_col;

    find_char(game->map, 'G', &goal_row, &goal_col);
    
    /* Check win condition */
    if (game->player_row == goal_row && game->player_col == goal_col) {
        game->game_over = 1; /* Win */
    }
    /* Check lose condition */
    else if (current_pos_char == '!') {
        game->game_over = -1; /* Lose */
    }
    /* Check for trap activation */
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
 * Spreads water one block in each cardinal direction using a flood-fill approach.
 */
static void spread_water(GameState* game) {
    int i, j;
    /* Create a temporary map to mark new water locations to avoid chain reactions in one turn */
    char** temp_grid = copy_map_data_from_source(game->map);

    if(temp_grid == NULL) return; /* Could not allocate memory */

    for (i = 1; i < game->map->rows + 1; i++) {
        for (j = 1; j < game->map->cols + 1; j++) {
            if (game->map->grid[i][j] == '!') {
                /* Check and mark adjacent cells for flooding in the temp grid */
                if (game->map->grid[i - 1][j] == ' ') temp_grid[i - 1][j] = '!';
                if (game->map->grid[i + 1][j] == ' ') temp_grid[i + 1][j] = '!';
                if (game->map->grid[i][j - 1] == ' ') temp_grid[i][j - 1] = '!';
                if (game->map->grid[i][j + 1] == ' ') temp_grid[i][j + 1] = '!';
            }
        }
    }
    
    /* Free the old grid and replace it with the updated one */
    free_map_grid(game->map->grid, game->map->rows + 2);
    game->map->grid = temp_grid;
}

