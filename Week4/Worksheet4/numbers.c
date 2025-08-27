/**
 * @brief contains the main() function 
 * which includes appropriate testing code for the functions just created.
 */

 #include <stdio.h>
 #include "order.h"
 #include "user_input.h"

 void printState(const char* message, int n1, int n2, int n3)
 {
     printf("%-20s: n1=%d, n2=%d, n3=%d\n", message, n1, n2, n3);
 }

 int main()
 {
    int n1, n2, n3; /*declared initial values*/
    char sort_choice;
    SortFuncPtr selectedSortFunction; /* Variable to hold the function pointer SortFuncPtr*/


    /* call readInts() to get values from the user. */
    readInts(&n1, &n2, &n3, &sort_choice); 

    printState("Initial values: ", n1, n2, n3);

    /*get the appropriate function pointer from order() funciton */
    selectedSortFunction = order(sort_choice); 

    if (selectedSortFunction != NULL) {
        selectedSortFunction(&n1, &n2, &n3);
        printState("SOrted value: ", n1, n2, n3);
    }
    else {
        printf("Invalid sort choice '%c'.", sort_choice);
    }
    return 0;
 }
