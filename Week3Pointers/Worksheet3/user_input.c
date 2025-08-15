#include <stdio.h>
#include "user_input.h"

void readInts(int *p1, int *p2, int *p3, char *choice) /* Addresses to store values from the user*/
{
    printf("Please enter the 1st integer: ");
    scanf("%d", p1); /*Reads integer from user input and store it at pointer p1.*/
    printf("Please enter the 2nd integer: ");
    scanf("%d", p2);
    printf("Please enter the 3rd integer: ");
    scanf("%d", p3);

    printf("Enter 'a' for ascending or 'd' for descending order: ");
    scanf(" %c", choice); /*space before % tells scanf to skip leftover whitespace*/
}