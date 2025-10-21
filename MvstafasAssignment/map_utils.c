/*
 * map_utils.c
 *
 * Implements various map utility functions: finding characters, replacing characters,
 * and creating map copies.
 */

#include <stdlib.h>
#include <string.h>
#include "map.h"

/**
 * @brief Finds the first occurrence of a target character in the inner map grid.
 * * @param map A pointer to the Map structure.
 * @param target The character to find.
 * @param row Output pointer for the row index (1-indexed).
 * @param col Output pointer for the column index (1-indexed).
 */
void find_char(Map* map, char target, int* row, int* col) {
    int i, j;
    *row = -1; /* Default to not found */
    *col = -1;
    
    /* Iterate over the inner grid (excluding the '*' border) */
    for (i = 1; i < map->rows + 1; i++) {
        for (j = 1; j < map->cols + 1; j++) {
            if (map->grid[i][j] == target) {
                *row = i;
                *col = j;
                return; /* Stop on first match */
            }
        }
    }
}

/**
 * @brief Replaces all occurrences of a target character with a replacement character.
 * * @param map A pointer to the Map structure.
 * @param target The character to be replaced.
 * @param replacement The character to replace with.
 */
void replace_char(Map* map, char target, char replacement) {
    int i, j;
    /* Iterate over the inner grid (excluding the '*' border) */
    for (i = 1; i < map->rows + 1; i++) {
        for (j = 1; j < map->cols + 1; j++) {
            if (map->grid[i][j] == target) {
                map->grid[i][j] = replacement;
            }
        }
    }
}

/**
 * @brief Creates a deep copy of the map grid data.
 * * Allocates new memory for the grid and copies all characters.
 *
 * @param source_map The map whose grid is to be copied.
 * @return A pointer to the new character grid (char**), or NULL on failure.
 */
char** copy_map_data_from_source(Map* source_map) {
    int i, j;
    char** new_grid;

    if (source_map == NULL || source_map->grid == NULL) {
        return NULL;
    }

    /* Allocate memory for the row pointers (rows + 2 for border) */
    new_grid = (char**)malloc((source_map->rows + 2) * sizeof(char*));
    if (new_grid == NULL) {
        return NULL;
    }

    /* Allocate and copy data for each row */
    for (i = 0; i < source_map->rows + 2; i++) {
        /* Allocate memory for the row data (cols + 2 for border) */
        new_grid[i] = (char*)malloc((source_map->cols + 2) * sizeof(char));
        if (new_grid[i] == NULL) {
            /* Cleanup already allocated rows on failure */
            for (j = 0; j < i; j++) {
                free(new_grid[j]);
            }
            free(new_grid);
            return NULL;
        }
        /* Copy the actual row data */
        memcpy(new_grid[i], source_map->grid[i], (source_map->cols + 2) * sizeof(char));
    }
    return new_grid;
}
