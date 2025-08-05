/**
 * powers.c
 * 
 * This file contains function next_power_of_two(), which returns the next 
 * power of 2 in sequence. 
 * 
 */

#include <stdio.h> // Standard input/output librar for printf
#include <limits.h> // For INT_MAX

int powersInc(void)
{
    static int power =1; // Initialise current power to 1. Static variable. 
    int result;

    if (pow < INT_MAX /2 )
    {
        power *= 2;
        result = power;
    }
    else
    {
        result = power;
        printf("Doing function again will cause overflow.\n");
        #ifdef DEBUG
            // If DEBUG is defined durin compilation. 
            printf("Current power is %d, which is the maximum value.\n", power); 
        #endif
    
        
    }
    return result;
}

/**
 * @brief The main function tests the powersINC() function. 
 * Calls the powersInc() function 32 times to demonstrate the sequence and the overflow protection.
 * If function is called more than 31 times, an integer oberflow will occur and result will be invalid.  
 * @return int Returns 0 on successful execution.
 */
int main(void)
{
    printf("Testing powersInc function:\n");
    for (int = 0; i < 32; i++)
    {
        int current_power = powersInc();
        printf("Next power of 2: %d\n", powersInc());
    }
    printf("End of testing.\n");
    return 0;
}