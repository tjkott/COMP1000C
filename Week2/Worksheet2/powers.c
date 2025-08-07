#include <stdio.h> /*Standard input/output librar for printf */ 
#include <limits.h>
#include "powers.h" /*Include the header file for function prototypes */ 
/*
 * powers.c
 * 
 * This file contains function next_power_of_two(), which returns the next 
 * power of 2 in sequence. 
 * 
 */


int powersInc(void)
{
    /* Initialise current power to 1. This is a static variable, so this */
    /* initialisation only happens on the first function call. */
    static int power = 1;
    int result;

    /* Check if multiplying the current power by 2 would exceed the */
    /* maximum value for an integer. */
    if (power < INT_MAX / 2)
    {
        /* If it's safe, calculate the next power of two. */
        power *= 2;
        result = power;
    }
    else
    {
        /* If the next operation would cause an overflow, return the current */
        /* power and print a warning. */
        result = power;
        printf("Warning: Doing function again will cause overflow.\n");

        /* The following block is only compiled if DEBUG is defined. */
        /* You can compile with the flag: gcc -DDEBUG powers.c -o powers */
        #ifdef DEBUG
            /* If DEBUG is defined during compilation, print this extra message. */
            printf("DEBUG: Current power is %d, which is the maximum value before overflow.\n", power);
        #endif
    }
    return result;
}