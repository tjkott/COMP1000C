/*
 * map_loader.c
 *
 * Implements the function to load the map from a file and initialize the grid.
 */

#include <stdio.h>
#include <stdlib.h>
#include "map.h"

/* External memory management function */
void free_map_grid(char** grid, int rows);

/**
 * @brief Loads a map from a text file into a Map structure.
 * * Reads dimensions, allocates memory for the grid, adds a border,
 * and populates the grid based on numeric codes in the file.
 *
 * @param filename The path to the map file.
 * @return A pointer to the fully constructed Map structure, or NULL on failure.
 */
Map* loadMap(char* filename) {
    FILE* file;
    Map* map;
    int i, j;
    int objectcode; 

    file = fopen(filename, "r"); 
    if (file == NULL) { 
        perror("Error opening map file");
        return NULL; 
    }

    map = (Map*)malloc(sizeof(Map));
    if (map == NULL) {
        perror("Failed to allocate memory for map struct");
        fclose(file);
        return NULL;
    }
    
    /* Read map dimensions (rows and columns) from the file header */
    if (fscanf(file, "%d %d", &map->rows, &map->cols) != 2) {
        fprintf(stderr, "Error: Invalid map dimensions in file.\n");
        free(map);
        fclose(file);
        return NULL;
    }

    /* Allocate memory for the grid pointers (rows + 2 for the border) */
    map->grid = (char**)malloc((map->rows + 2) * sizeof(char*));
    if (map->grid == NULL) {
        perror("Failed to allocate memory for map grid row pointers");
        free(map);
        fclose(file);
        return NULL;
    }

    /* Allocate memory for each row (cols + 2 for the border) */
    for (i = 0; i < map->rows + 2; i++) {
        map->grid[i] = (char*)malloc((map->cols + 2) * sizeof(char));
        if (map->grid[i] == NULL) {
            perror("Failed to allocate memory for map row data");
            /* Clean up already allocated rows before failing */
            for (j = 0; j < i; j++) {
                free(map->grid[j]);
            }
            free(map->grid);
            free(map);
            fclose(file);
            return NULL;
        }
    }

    /* Create the '*' border around the map */
    for (j = 0; j < map->cols + 2; j++) {
        map->grid[0][j] = '*'; /* Top border */
        map->grid[map->rows + 1][j] = '*'; /* Bottom border */
    }
    for (i = 1; i < map->rows + 1; i++) {
        map->grid[i][0] = '*'; /* Left border */
        map->grid[i][map->cols + 1] = '*'; /* Right border */
    }

    /* Read the map content from the file (numeric codes) */
    for (i = 1; i < map->rows + 1; i++) {
        for (j = 1; j < map->cols + 1; j++) {
            if (fscanf(file, "%d", &objectcode) != 1) {
                map->grid[i][j] = ' '; /* Default to empty if read fails */
                continue;
            }
            /* Convert numeric codes to character representations */
            switch (objectcode) {
                case 0: map->grid[i][j] = ' '; break; /* Empty space */
                case 1: map->grid[i][j] = 'O'; break; /* Boulder */
                case 2: map->grid[i][j] = '!'; break; /* Initial Water */
                case 3: map->grid[i][j] = 'X'; break; /* Water Blocker */
                case 4: map->grid[i][j] = '@'; break; /* Trap Trigger */
                case 5: map->grid[i][j] = 'P'; break; /* Player Start */
                case 6: map->grid[i][j] = 'G'; break; /* Goal */
                default: map->grid[i][j] = ' '; break; /* Unknown/Empty */
            }
        }
    }

    fclose(file);
    return map;
}
