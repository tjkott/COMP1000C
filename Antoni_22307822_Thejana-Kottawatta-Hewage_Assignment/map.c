/*
 * map.c
 *
 * Implements functions for loading the map from a file, printing it to the terminal, and other map-related utilities.
 */

#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "color.h"

/*
 * Loads a map from a text file into a Map struct.
 * Returns a pointer to the new Map struct, or NULL on failure.
 */
Map* load_map(char* filename) { 
    FILE* file = NULL;
    Map* map = NULL;
    int i = 0, j = 0; 
    int object_code;
    int success = 0; /* Status flag */
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening map file");
    } else {
        map = (Map*)malloc(sizeof(Map)); /* malloc for map struct*/
        if (map == NULL) {
            perror("Failed to allocate memory for map");
        } else {
            map->grid = NULL; 
            if (fscanf(file, "%d %d", &map->rows, &map->cols) != 2) { /* Read map dimensions */
                fprintf(stderr, "Error: Invalid map dimensions in file.\n");
            } else {
                map->grid = (char**)malloc((map->rows + 2) * sizeof(char*)); /* Allocate memory for the row pointers */
                if (map->grid == NULL) {
                    perror("Failed to allocate memory for map grid");
                } else {
                    success = 1; /* Assume success unless a row allocation fails */
                    for (i = 0; i < map->rows + 2 && success; i++) {
                        map->grid[i] = (char*)malloc((map->cols + 2) * sizeof(char)); /* Allocate memory for each row */
                        if (map->grid[i] == NULL) {
                            perror("Failed to allocate memory for map row");
                            success = 0;
                            for (j = 0; j < i; j++) {
                                free(map->grid[j]);
                            }
                        }
                    }
                    if (success) { /* populate the map if all malloc is successful*/
                        /* Create borders */
                        for (j = 0; j < map->cols + 2; j++) {
                            map->grid[0][j] = '*';
                            map->grid[map->rows + 1][j] = '*';
                        }
                        for (i = 1; i < map->rows + 1; i++) {
                            map->grid[i][0] = '*';
                            map->grid[i][map->cols + 1] = '*';
                        }
                        for (i = 1; i < map->rows + 1; i++) {
                            for (j = 1; j < map->cols + 1; j++) {
                                if (fscanf(file, "%d", &object_code) != 1) {
                                    map->grid[i][j] = ' '; /* Default on read fail */
                                } else {
                                    switch (object_code) {
                                        case 0: map->grid[i][j] = ' '; break;
                                        case 1: map->grid[i][j] = 'O'; break;
                                        case 2: map->grid[i][j] = '!'; break;
                                        case 3: map->grid[i][j] = 'X'; break;
                                        case 4: map->grid[i][j] = '@'; break;
                                        case 5: map->grid[i][j] = 'P'; break;
                                        case 6: map->grid[i][j] = 'G'; break;
                                        default: map->grid[i][j] = ' '; break;
                                    }
                                }
                            }
                        }
                    } else {
                        /* Free the grid pointer array if row allocation failed */
                        free(map->grid);
                        map->grid = NULL;
                    }
                }
            }
        }
        /* Close the file if it was opened */
        fclose(file);
    }

    /* Central cleanup and return logic */
    if (!success) {
        if (map != NULL) {
            /* If grid allocation failed but map struct was allocated */
            if (map->grid != NULL) {
                 /* This case is handled above where rows are freed */
            }
            free(map); /* Free map struct if grid alloc/read failed */
        }
        map = NULL; /* Ensure NULL is returned on any failure */
    }

    /* Single return statement */
    return map;
}

/*
 * Frees the memory allocated for a 2D char array (the map grid).
 */
void free_map_grid(char** grid, int rows) {
    int i;
    if (grid != NULL) {
        for (i = 0; i < rows; i++) {
            if (grid[i] != NULL) {
                free(grid[i]);
            }
        }
        free(grid);
    }
}

/*
 * Frees all memory associated with a Map struct.
 */
void free_map(Map* map) {
    if (map != NULL) {
        free_map_grid(map->grid, map->rows + 2); 
        free(map);
    }
}

/*
 * Prints the map to the console, clearing the screen first and applying colors.
 */
void print_map(Map* map) {
    int i, j;
    system("clear");
    /* ANSI escape code to clear screen and move cursor to top-left */
    printf("\033[2J\033[H"); 
    
    for (i = 0; i < map->rows + 2; i++) {
        for (j = 0; j < map->cols + 2; j++) {
            char c = map->grid[i][j];
            switch (c) {
                case '@':
                    setBackground("red");
                    printf("%c", c);
                    setBackground("reset");
                    break;/* "break" is fine when using a swtich case.*/
                case 'G':
                    setBackground("green");
                    printf("%c", c);
                    setBackground("reset");
                    break;
                case '!':
                    setBackground("blue");
                    printf("%c", c);
                    setBackground("reset");
                    break;
                default:
                    printf("%c", c);
                    break;
            }
        }
        printf("\n");
    }
    printf("Press 'w','s','a','d' to move, 'u' to undo.\n");
}

/*
 * Finds the coordinates of the first occurrence of a target character in the map.
 */
void find_char(Map* map, char target, int* row, int* col) { 
    int i, j;
    int found = 0; /* Flag to stop searching once found */

    *row = -1;
    *col = -1;

    /* Loop through playable area */
    for (i = 1; i < map->rows + 1 && !found; i++) {
        for (j = 1; j < map->cols + 1 && !found; j++) {
            if (map->grid[i][j] == target) {
                *row = i;
                *col = j;
                found = 1; /* Set flag to exit loops */
            }
        }
    }
}

/*
 * Replaces all occurrences of a target character on the map with a replacement character.
 */
void replace_char(Map* map, char target, char replacement) { 
    int i, j;
    for (i = 1; i < map->rows + 1; i++) {
        for (j = 1; j < map->cols + 1; j++) {
            if (map->grid[i][j] == target) {
                map->grid[i][j] = replacement;
            }
        }
    }
}

/*
 * Creates a "deep copy" of a map's grid data.
 * Returns a pointer to the new grid, or NULL on failure.
 */
char** copy_map_data_from_source(Map* source_map) {
    int i = 0, j = 0; /* loop counters */
    char** new_grid = NULL;
    int success = 0; /* Status flag */

    /* Basic validation */
    if (source_map != NULL && source_map->grid != NULL) {
        /* Allocate memory for row pointers */
        new_grid = (char**)malloc((source_map->rows + 2) * sizeof(char*));
        if (new_grid != NULL) {
            success = 1; /* Assume success unless a row allocation fails */
            /* Allocate memory for each row and copy data */
            for (i = 0; i < source_map->rows + 2 && success; i++) {
                new_grid[i] = (char*)malloc((source_map->cols + 2) * sizeof(char));
                if (new_grid[i] == NULL) {
                    success = 0; /* Mark failure */
                    /* Clean up previously allocated rows on failure */
                    for (j = 0; j < i; j++) {
                        free(new_grid[j]);
                    }
                } else {
                    /* Copy data for the current row */
                    for (j = 0; j < source_map->cols + 2; j++) {
                        new_grid[i][j] = source_map->grid[i][j];
                    }
                }
            }
            /* If any row allocation failed, free the row pointer array */
            if (!success) {
                free(new_grid);
                new_grid = NULL;
            }
        }
    }
    return new_grid;/* Single return statement */
}
