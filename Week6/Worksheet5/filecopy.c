/**
 * @brief filecopy.c - Simple program to copy one file to another. 
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) { // file pointers/ source and destination filename command line param
    /**Parameters:
     * int argc = the number of command line arguments passed into the funciton. 
     * char argv = teh array of strings representing the 3 arguments. 
     * 1 = program name, 2 = source file, 3 = dest file
     * e.g.: ./myprogram source_file destination_file
     */

    FILE *sourceFile, *destFile;
    int ch; // holds one character read from the file stored as int. 

    // File modes
    sourceFile = fopen(argv[1], "rb"); // rb to handle all file types, not just text.
    destFile = fopen(argv[2], "wb");

    // Exceptions: Check if program is run as ./program source.txt dest.txt
    if (argc != 3){
        // strderr: prints to the error stream. 
        fprintf(stderr, "Usage: %s <source_file> <dest_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Error checking: opening files
    if (sourceFile == NULL) {
        perror(argv[1]); // Prints system error message pre-fixed with argv i.e. file name. 
        exit(EXIT_FAILURE);
    }
    if (destFile == NULL){
        perror(argv[2]);
        exit(EXIT_FAILURE);
    }

    // While until EOF is reached, returns the character stored at 'ch'/ 
    while ((ch = fgetc(sourceFile)) != EOF){
        //fputc() writes to the destination file. 
        fputc(ch, destFile);
    }

    // Close files
    fclose(sourceFile);
    fclose(destFile);
}

