/*
 * map_memory.c
 *
 * Implements functions for freeing the map's dynamically allocated memory.
 */
#include <stdlib.h>
#include "map.h"

/**
 * @brief Frees all memory allocated for the 2D character grid.
 * * @param grid The grid (char**) to free.
 * @param rows The number of rows in the grid (including border rows).
 */
void free_map_grid(char** grid, int rows) {
    int i;
    if (grid != NULL) {
        /* Free each individual row first */
        for (i = 0; i < rows; i++) {
            if (grid[i] != NULL) {
                free(grid[i]);
            }
        }
        /* Free the array of row pointers */
        free(grid);
    }
}

/**
 * @brief Frees the entire Map structure, including its grid.
 * * @param map A pointer to the Map structure to free.
 */
void free_map(Map* map) {
    if (map != NULL) {
        /* Rows includes the two border rows */
        free_map_grid(map->grid, map->rows + 2);
        free(map); /* Free the Map struct itself */
    }
}
