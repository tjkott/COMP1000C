/**
 * @brief display.c - reads data from a text file into a 2D array.
 * Then passes the array to plot.c declared in plot.h.
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h> // for strcmp
 #include "plot.h"

 int main(int argc, char *argv[]){
    FILE *dataFile;
    int rows, cols;
    double **data = NULL;
    int i, j;

    // EXCEPTIONS;
    // (a) Check if command line accepts a filemname as a parameter
    if (argc != 2){
        fprintf(stderr, "Usage: %s <datafile>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (strcmp(argv[1], "-") == 0) {
        dataFile = stdin; //standard input
        printf("Reading from stdin.\n");
    } else {
        dataFile = fopen(argv[1], "r");
        if (dataFile == NULL) {
            perror("Error opening the file.");
            exit(EXIT_FAILURE);
        }
    }
    
    //reads 1st two integers of the file spcifies the rows, col
    if (fscanf(dataFile, "%d %d", &rows, &cols) != 2){ 
        fprintf(stderr, "Error: Could not read array dimensions.\n");
        fclose(dataFile);
        exit(EXIT_FAILURE);
    }

    //(b) After reading the first  line of the file, memory allocate a 2D array of the required size.
    
    // Allocate enough memory to hold rows pointers, each pointer pointing to a double array.
    data = (double **)malloc(rows * sizeof(double *)); 
    //if allocation fails -> free previously allocated memory and exit
    if (data == NULL){
        perror("Malloc failed for row pointers.");
        fclose(dataFile);
        exit(EXIT_FAILURE);
    }

    // Allocate enough memory for each row.
    for (i = 0; i < rows; i++){
        // for each row, allocate an array of 'cols' doubles
        data[i] = (double *)malloc(cols * sizeof(double)); \

        if (data[i] == NULL){
            perror("Malloc failed for a row");
            for (j = 0; j < 1; j++) {
                free(data[j]);
            }
            free(data);
            fclose(dataFile);
            exit(EXIT_FAILURE);
        }
    }
    
    // (c) read in all values and fill the arrays. 
    for (i = 0; i < rows; i++){
        for (j = 0; j < cols; j++){

            // If file ends too soon before all values are filled into the arrays. 
            if (fscanf(dataFile, "%lf", &data[i][j]) != 1){
                fprintf(stderr, "Error: FIle ended prematurely.\n");
                // Free allocated memory before exiting
                for (int k = 0; k < rows; k++){
                    free(data[k]);
                }
                free(data);
                fclose(dataFile);
                exit(EXIT_FAILURE);
            }
        }
    }

    fclose(dataFile);

    // (d) Write the array to a file, using the same format as in the previous question. 
    printf("Data read successfully. Now plotting ...\n");
    plot(data, rows, cols);

    //(e) Implement approapriate error handling, and clean up the allocated memroy.

    // Free each row
    for (i = 0; i < rows; i++){
        free(data[i]);
    }
    // Free the array of row poitners. 
    free(data);
    return EXIT_SUCCESS;
}
