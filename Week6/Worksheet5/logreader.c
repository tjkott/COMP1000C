/**
 * @brief logreader.c - Read UNIX log file
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 512

int main(int argc, char *argv[]){

    // (1) File pointers
    FILE *logFile;

    //(2) Variable to hold info on the log entry. 
    char month[4], process[100];
    int day, hour, min, sec;

    // Buffer for the free form message at the end of eac line. 
    char message[MAX_LINE_LENGTH];

    // (3) Command line parameter exceptions handling
    if (argc != 2){
        // fprint() writes formatted data. 
        fprintf(stderr, "Usage: %s <logfile>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // (4) Read the file line by line
    logFile = fopen(argv[1], "r");
    if (logFile == NULL){
        fprintf(stderr, "Error opening file: %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    while (fscanf(logFile, "%3s %d %d:%d:%d %99[^:]:", month, &day, &hour, &min, &sec, process) == 6){
        // %99[^:] = reads up to 99 characters from file until a colon ":" s found. 
        // Loop only continues if exactly 6 items are successfully read. 
        fgetc(logFile);

        // Reading the rest of the current line into new variable called 'message'. 
        // fgets() reads up to n-1 i.e. MAX_LINE_LENGTH-1 chars (until new line)
        if (fgets(message, MAX_LINE_LENGTH, logFile) != NULL){
            // strstr() checks if substring "fail" exists anywhere in the message. 
            if (strstr(message, "fail) != NULL")){
                // long function is for potentially large values. 
                long sumSec = hour * 3600L + min * 60L + sec;

                // print total seconds + ":" + message
                printf("%ld: %s", sumSec, message);
            }
            
        }

    }
    fclose(logFile);
    return EXIT_SUCCESS;

}