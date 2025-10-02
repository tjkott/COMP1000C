/*
 * map.h
 *
 * Header file for map-related functions.
 * Declares the Map struct and functions for loading and managing the map.
 */

#ifndef MAP_H
#define MAP_H

/* Represents the game map */
typedef struct {
    int rows;
    int cols;
    char** grid;
} Map;

/* Function prototypes for map operations */
Map* load_map(char* filename);
void free_map(Map* map);
void print_map(Map* map);
void find_char(Map* map, char target, int* row, int* col);
void replace_char(Map* map, char target, char replacement);
char** copy_map_data_from_source(Map* source_map);
void free_map_grid(char** grid, int rows);

#endif /* MAP_H */
