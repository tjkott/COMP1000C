/* 
 * game_water.c
 *
 * Implements the flood-fill (water spreading) mechanism.
 */
#include <stdlib.h>
#include "game.h"
#include "map.h" /* For map utility functions like copy_map_data_from_source */

/**
 * @brief Spreads water ('!') to adjacent empty cells (' ').
 * * This is an implementation of a single step of a flood-fill algorithm.
 * It copies the grid, updates the water based on the *previous* state, 
 * and then replaces the map's grid with the new state.
 * This is a private helper function originally, now a standalone module function.
 * * @param game A pointer to the current GameState.
 */
void spreadWater(GameState* game) {
    int i, j;
    
    /* Create a copy of the current grid to calculate the next state */
    char** temp_grid = copy_map_data_from_source(game->map);
    if(temp_grid == NULL) return; /* Handle allocation failure */

    /* Iterate over the map's inner cells (excluding the outer '*' border) */
    for (i = 1; i < game->map->rows + 1; i++) {
        for (j = 1; j < game->map->cols + 1; j++) {
            
            /* If a cell is currently water ('!')... */
            if (game->map->grid[i][j] == '!') {
                
                /* Check surrounding empty cells and mark them as water in the *new* grid */
                if (game->map->grid[i-1][j] == ' ') temp_grid[i-1][j] = '!';
                if (game->map->grid[i+1][j] == ' ') temp_grid[i+1][j] = '!';
                if (game->map->grid[i][j-1] == ' ') temp_grid[i][j-1] = '!';
                if (game->map->grid[i][j+1] == ' ') temp_grid[i][j+1] = '!';
            }
        }
    }
    
    /* Free the old grid data */
    free_map_grid(game->map->grid, game->map->rows + 2);
    
    /* Set the game's map grid to the newly calculated grid */
    game->map->grid = temp_grid;
}
