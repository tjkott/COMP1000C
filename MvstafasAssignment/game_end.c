/*
 * game_end.c
 *
 * Implements the logic for checking win/loss conditions.
 */
#include <stdio.h>
#include "game.h"
#include "game_trap.h"
#include "color.h" /* For coloring the win/loss messages */
#include "newSleep.h" /* For pausing the screen after game ends */

/**
 * @brief Checks if the player has reached the goal or been submerged.
 * * Updates the game->game_over status and prints the final message.
 * This is a private helper function originally, now a standalone module function.
 * * @param game A pointer to the current GameState.
 */
void check_game_over(GameState* game) {
    char current_pos_char = game->map->grid[game->player_row][game->player_col];
    int goal_row, goal_col;

    /* Find the goal position ('G') on the map */
    find_char(game->map, 'G', &goal_row, &goal_col);
    
    /* --- Win Condition Check --- */
    if (game->player_row == goal_row && game->player_col == goal_col) {
        game->game_over = 1; /* Set status to Win */
        
        /* Print the final map state before the message */
        print_map(game->map); 
        
        /* Print a celebratory message in green */
        setForeground("green");
        printf("\nYou win!\n");
        setForeground("reset");
        newSleep(2.0f); /* Pause for the user to see the result */
    }
    /* --- Loss Condition Check (Drowned by water) --- */
    else if (current_pos_char == '!') {
        game->game_over = -1; /* Set status to Lose */
        
        /* The player is now effectively replaced by water for the final display */
        game->map->grid[game->player_row][game->player_col] = '!'; 
        
        /* Print the final map state */
        print_map(game->map);
        
        /* Print a losing message in red */
        setForeground("red");
        printf("\nYou lose!\n");
        setForeground("reset");
        newSleep(2.0f); /* Pause for the user to see the result */
    }
    /* --- Trap Trigger Check --- */
    else if (current_pos_char == '@') {
        /* If the player steps on a trap, trigger it (water starts flowing) */
        triggerTrap(game);
    }
}
