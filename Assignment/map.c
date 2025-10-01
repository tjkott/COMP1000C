/*
 * map.c
 *
 * Implements functions for loading the map from a file,
 * printing it to the terminal, and other map-related utilities.
 */

#include <stdio.h>
#include <stdlib.h>
#include "map.h"

/*
 * Loads a map from a text file into a Map struct.
 */
Map* load_map(char* filename) {
    FILE* file;
    Map* map;
    int i, j;
    int object_code;

    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening map file");
        return NULL;
    }

    map = (Map*)malloc(sizeof(Map));
    if (map == NULL) {
        perror("Failed to allocate memory for map");
        fclose(file);
        return NULL;
    }

    /* Read map dimensions */
    if (fscanf(file, "%d %d", &map->rows, &map->cols) != 2)
    {
        fprintf(stderr, "Error: Invalid map dimensions in file.\n");
        free(map);
        fclose(file);
        return NULL;
    }

    /* Allocate memory for the grid including borders */
    map->grid = (char**)malloc((map->rows + 2) * sizeof(char*));
    if (map->grid == NULL) {
        perror("Failed to allocate memory for map grid");
        free(map);
        fclose(file);
        return NULL;
    }

    for (i = 0; i < map->rows + 2; i++) {
        map->grid[i] = (char*)malloc((map->cols + 2) * sizeof(char));
        if (map->grid[i] == NULL) {
            perror("Failed to allocate memory for map row");
            /* Clean up previously allocated rows */
            for (j = 0; j < i; j++) {
                free(map->grid[j]);
            }
            free(map->grid);
            free(map);
            fclose(file);
            return NULL;
        }
    }

    /* Create borders */
    for (j = 0; j < map->cols + 2; j++) {
        map->grid[0][j] = '*';
        map->grid[map->rows + 1][j] = '*';
    }
    for (i = 1; i < map->rows + 1; i++) {
        map->grid[i][0] = '*';
        map->grid[i][map->cols + 1] = '*';
    }

    /* Read map content by converting integer codes to characters */
    for (i = 1; i < map->rows + 1; i++) {
        for (j = 1; j < map->cols + 1; j++) {
            if(fscanf(file, "%d", &object_code) == 1)
            {
                switch (object_code) {
                    case 0: map->grid[i][j] = ' '; break; /* Path */
                    case 1: map->grid[i][j] = 'O'; break; /* Wall */
                    case 2: map->grid[i][j] = '!'; break; /* Water */
                    case 3: map->grid[i][j] = 'X'; break; /* Trapdoor */
                    case 4: map->grid[i][j] = '@'; break; /* Trap */
                    case 5: map->grid[i][j] = 'P'; break; /* Player */
                    case 6: map->grid[i][j] = 'G'; break; /* Goal */
                    default: map->grid[i][j] = ' '; break; /* Default to path */
                }
            }
            else
            {
                map->grid[i][j] = ' '; /* Default if read fails */
            }
        }
    }

    fclose(file);
    return map;
} /* This was the missing closing brace */

/*
 * Frees the 2D char array used for the map grid.
 */
void free_map_grid(char** grid, int rows) {
    int i;
    if (grid != NULL) {
        for (i = 0; i < rows; i++) {
            free(grid[i]);
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
 * Prints the map to the console with colors.
 */
void print_map(Map* map) {
    int i, j;
    /* Clear the screen before printing */
    printf("\033[2J\033[H");
    
    for (i = 0; i < map->rows + 2; i++) {
        for (j = 0; j < map->cols + 2; j++) {
            char c = map->grid[i][j];
            switch (c) {
                case '@': /* Trap */
                    printf("\x1b[41m%c\x1b[0m", c); /* Red background */
                    break;
                case 'G': /* Goal */
                    printf("\x1b[42m%c\x1b[0m", c); /* Green background */
                    break;
                case '!': /* Water */
                    printf("\x1b[44m%c\x1b[0m", c); /* Blue background */
                    break;
                default:
                    printf("%c", c);
                    break;
            }
        }
        printf("\n");
    }
    printf("Press 'w', 's', 'a', 'd' to move, 'u' to undo.\n");
}

/*
 * Finds the first occurrence of a character on the map.
 */
void find_char(Map* map, char target, int* row, int* col) {
    int i, j;
    *row = -1;
    *col = -1;
    for (i = 1; i < map->rows + 1; i++) {
        for (j = 1; j < map->cols + 1; j++) {
            if (map->grid[i][j] == target) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

/*
 * Replaces all occurrences of a character on the map.
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
 * Creates a deep copy of a map's grid data.
 */
char** copy_map_data_from_source(Map* source_map) {
    int i, j;
    char** new_grid;

    if (source_map == NULL || source_map->grid == NULL) {
        return NULL;
    }

    new_grid = (char**)malloc((source_map->rows + 2) * sizeof(char*));
    if (new_grid == NULL) {
        return NULL;
    }

    for (i = 0; i < source_map->rows + 2; i++) {
        new_grid[i] = (char*)malloc((source_map->cols + 2) * sizeof(char));
        if (new_grid[i] == NULL) {
            /* Clean up previously allocated memory */
            for (j = 0; j < i; j++) {
                free(new_grid[j]);
            }
            free(new_grid);
            return NULL;
        }
        for (j = 0; j < source_map->cols + 2; j++) {
            new_grid[i][j] = source_map->grid[i][j];
        }
    }
    return new_grid;
}

