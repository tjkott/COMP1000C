/**
 * @brief generate.c -
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "randomarray.h"

int main(int argc, char *argv[]){
    FILE *outFile;
    int rows, cols;
    double **data = NULL;
    int i, j;
    const int SMOOTHNESS = 5;

    // (a)) Only accept 3 commandline parameters: filename, 2 inteegers represnting the number of rows + cols. 
    if (argc != 4) {
        // otherwise throw error
        fprintf(stderr, "Usage: %s <filename> <rows> <cols>\n", argv[0]);
        exit(EXIT_FAILURE);

    }
    

    // (b) llocate a 2D array of the required size. 

    // Convert string args to ints. 
    rows = atoi(argv[2]);
    cols = atoi(argv[3]);

    data = (double **)malloc(rows * sizeof(double *));
    if (data == NULL) {
        perror("Malloc failed as no data");
        exit(EXIT_FAILURE);
    
    }
    for (i = 0; i < rows; i++) {
        data[i] = (double *)malloc(cols * sizeof(double));
        if (data[i] == NULL) {
            perror("Malloc failed for rows");
            for (j = 0; j < i; j++) {
                free(data[j]);

            }
            free(data);
            exit(EXIT_FAILURE);
        }
    }

    // (c) Pass the array to the randomArray(0 function. 
    randomArray(data, rows, cols, SMOOTHNESS);
    // Fill the array generated with random values.

    // (d) Write th array to a file. 

    if (strcmp(argv[1], "-") == 0) {
        outFile = stdout;
    } else {
        outFile = fopen(argv[1], "w"); // open the 2nd parameter file in write mode.
        if (outFile == NULL) {
            perror("Error: Could not open file");
            for (i = 0; i < rows; i++) {
                free(data[i]);
            }
            free(data);
            exit(EXIT_FAILURE);
        }
    }
    

    // write the dimensions of the array in the first line of the outFile.
    fprintf(outFile, "%d %d\n", rows, cols);

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            fprintf(outFile, "%f", data[i][j]);
        }
        fprintf(outFile, "\n");
        
    }
    fclose(outFile);


    // (e) Clean up allocated memory. 
    for (i = 0; i < rows; i++) {
        free(data[i]);
    
    }
    free(data);

    return EXIT_SUCCESS;

    

}
