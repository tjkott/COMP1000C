/**
 * bounds.c
 * 
 * Will take in 3 integers and performs bounds checking on an integer. 
 * 
 */
#include <stdio.h>
#include "macros.h"

int withinRangeInt(int low, int high, int value)
{
    if (value >= low && value <= high)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

int withinRangeDouble(double low, double high, double value)
{
    if (value >= low && value <= high)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

int withinRangeChar(char low, char high, char value)
{
    if (value >= low && value <= high)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

// Main function to test 3 above functions. 
// Prompts user for an input between 1 and 31, validates the input and
// calls the powersInc function from powers.c to calculate power of 2. 
int main(void)
{
    int userInput = 0;
    int i;

    // Loop to get valid user input.
    // The loop continues as long as the input is NOT between 1 and 31.
    do
    {
        printf("Please enter a number between 1 and 31: ");
        scanf("%d", &userInput);

        if (!BETWEEN(1, 31, userInput))
        {
            printf("Invalid input. Please try again.\n");
        }

    } while (!BETWEEN(1, 31, userInput));

    printf("\nCalculating powers of two %d times:\n", userInput);

    // Call the powersInc function the number of times specified by the user.
    for (i = 0; i < userInput; i++)
    {
        printf("Call %d: Result = %d\n", i + 1, powersInc());
    }

    return 0;
}