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

    /* call readInts() to get values from the user. */
    readInts(&n1, &n2, &n3, &sort_choice); 

    printState("Initial values: ", n1, n2, n3);

    /* For now don;t do anything with the input characteer, just sort ascending.*/
    ascending3(&n1, &n2, &n3);

    printState("Sorted ascending: ", n1, n2, n3);
    return 0;
 }