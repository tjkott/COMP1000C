/*
 * map.c
 *
 * Header file for map-related functions.
 * Now primarily handles the map structure and external function declarations.
 */

#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "color.h" /* Needed for colored printing */

/* Externally defined functions from map modules */
void free_map_grid(char** grid, int rows);
void free_map(Map* map);

/**
 * @brief Prints the current state of the map to the terminal.
 * * Clears the screen and iterates through the grid, applying color
 * for special elements like Trap, Goal, and Water.
 * * @param map A pointer to the Map structure to print.
 */
void print_map(Map* map) {
    int i, j;
    /* ANSI sequence to clear the screen and move cursor to (1,1) */
    printf("\033[2J\033[H"); 
    /* Fallback for terminals that don't support the above (e.g. some environments) */
    system("clear"); 
    
    for (i = 0; i < map->rows + 2; i++) {
        for (j = 0; j < map->cols + 2; j++) {
            char c = map->grid[i][j];
            switch (c) {
                case '@': /* Trap */
                    setBackground("red");
                    printf("%c", c);
                    setBackground("reset");
                    break;
                case 'G': /* Goal */
                    setBackground("green");
                    printf("%c", c);
                    setBackground("reset");
                    break;
                case '!': /* Water */
                    setBackground("blue");
                    printf("%c", c);
                    setBackground("reset");
                    break;
                default:
                    /* Print any other character (Player, Wall, Space, etc.) without special background */
                    printf("%c", c);
                    break;
            }
        }
        printf("\n"); /* Newline after each row */
    }
    printf("Press 'w','s','a','d' to move, 'u' to undo.\n");
}
