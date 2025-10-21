/*
 * game_move.c
 *
 * Contains the logic for player movement and interaction with map cells.
 */
#include "game.h"
#include "map.h" /* For map grid access */

/* Externally defined functions (from other game modules) */
void spreadWater(GameState* game);
void check_game_over(GameState* game);
void save_game_state(UndoHistory* history, GameState* current_state);

/**
 * @brief Attempts to move the player to a new position.
 * * Handles collision detection, updates player position, and checks for traps/win/loss.
 * This is a private helper function originally, now a standalone module function.
 * * @param game A pointer to the current GameState.
 * @param new_row The proposed new row index.
 * @param new_col The proposed new column index.
 */
void move_player(GameState* game, int new_row, int new_col) {
    /* Get the character at the destination */
    char target_char = game->map->grid[new_row][new_col];

    /* Check for impassable terrain: Walls ('*'), Boulders ('O'), and Blockers ('X') */
    if (target_char != '*' && target_char != 'O' && target_char != 'X') {
        
        /* Clear the player's old position */
        game->map->grid[game->player_row][game->player_col] = ' ';
        
        /* Update player coordinates */
        game->player_row = new_row;
        game->player_col = new_col;
        
        /* Check if the new position results in a win, loss, or trap trigger */
        check_game_over(game);

        /* Only proceed with map updates and water if the game is still ongoing */
        if(game->game_over == 0) {
            /* Place the player marker 'P' at the new valid location */
            game->map->grid[game->player_row][game->player_col] = 'P';
            
            /* If the trap has been activated, spread the water one step */
            if (game->trap_triggered == 1) {
                spreadWater(game);
                check_game_over(game); /* Re-check after water spreads, as it might drown the player */
            }
        }
        
        /* Save the state for undo functionality, but only if the game is still ongoing */
        if (game->game_over == 0) {
            save_game_state(game->undo_history, game);
        }
    }
}
