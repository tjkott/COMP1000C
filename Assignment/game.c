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

/* Private helper function prototypes */
static void move_player(GameState* game, int new_row, int new_col);
static void trigger_trap(GameState* game);
static void spread_water(GameState* game);
static void check_game_over(GameState* game);

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
        
        save_game_state(game->undo_history, game);
    }
    return game;
}

void free_game_state(GameState* game) {
    if (game != NULL) {
        free_map(game->map);
        free_undo_history(game->undo_history);
        free(game);
    }
}

void print_game_state(GameState* game) {
    print_map(game->map);
}

void process_input(GameState* game, char input) {
    int new_row = game->player_row;
    int new_col = game->player_col;

    if (game->game_over != 0) return;

    switch (input) {
        case 'w': new_row--; break;
        case 's': new_row++; break;
        case 'a': new_col--; break;
        case 'd': new_col++; break;
        case 'u': restore_game_state(game->undo_history, game); return;
        default: return;
    }
    move_player(game, new_row, new_col);
}

static void move_player(GameState* game, int new_row, int new_col) {
    char target_char = game->map->grid[new_row][new_col];

    if (target_char != '*' && target_char != 'O' && target_char != 'X') {
        game->map->grid[game->player_row][game->player_col] = ' ';
        game->player_row = new_row;
        game->player_col = new_col;
        
        check_game_over(game);

        if(game->game_over == 0) {
            game->map->grid[game->player_row][game->player_col] = 'P';
            if (game->trap_triggered == 1) {
                spread_water(game);
                check_game_over(game); /* Re-check after water spreads */
            }
        }
        
        if (game->game_over == 0) {
            save_game_state(game->undo_history, game);
        }
    }
}

static void check_game_over(GameState* game) {
    char current_pos_char = game->map->grid[game->player_row][game->player_col];
    int goal_row, goal_col;

    find_char(game->map, 'G', &goal_row, &goal_col);
    
    if (game->player_row == goal_row && game->player_col == goal_col) {
        game->game_over = 1; /* Win */
        print_map(game->map);
        setForeground("green");
        printf("\nYou win!\n");
        setForeground("reset");
        newSleep(2.0f);
    }
    else if (current_pos_char == '!') {
        game->game_over = -1; /* Lose */
        game->map->grid[game->player_row][game->player_col] = '!'; /* Ensure player is submerged */
        print_map(game->map);
        setForeground("red");
        printf("\nYou lose!\n");
        setForeground("reset");
        newSleep(2.0f);
    }
    else if (current_pos_char == '@') {
        trigger_trap(game);
    }
}

static void trigger_trap(GameState* game) {
    game->trap_triggered = 1;
    replace_char(game->map, '@', ' ');
    replace_char(game->map, 'X', ' ');
}

static void spread_water(GameState* game) {
    int i, j;
    char** temp_grid = copy_map_data_from_source(game->map);
    if(temp_grid == NULL) return;

    for (i = 1; i < game->map->rows + 1; i++) {
        for (j = 1; j < game->map->cols + 1; j++) {
            if (game->map->grid[i][j] == '!') {
                if (game->map->grid[i-1][j] == ' ') temp_grid[i-1][j] = '!';
                if (game->map->grid[i+1][j] == ' ') temp_grid[i+1][j] = '!';
                if (game->map->grid[i][j-1] == ' ') temp_grid[i][j-1] = '!';
                if (game->map->grid[i][j+1] == ' ') temp_grid[i][j+1] = '!';
            }
        }
    }
    
    free_map_grid(game->map->grid, game->map->rows + 2);
    game->map->grid = temp_grid;
}