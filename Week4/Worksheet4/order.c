#include <stdio.h>
#include "order.h"

/**
 * @brief Takes 2 int pointers and returns void. 
 * Static function only visible within this file. */ 
static void ascending2(int *p1, int *p2)
{
    if (*p1 > *p2)
    {
        int temp = *p1;
        *p1 = *p2;
        *p2 = temp;
    }
}

/**
 * @brief Takes 3 int pointers and returns the void. 
 * i.e. bubble sort for 3 elements. 
 */
void ascending3(int *p1, int *p2, int *p3)
{
    ascending2(p1, p2); /* Largest of the first 2 elements is in p2. */
    ascending2(p2, p3); /* largest of the last 2 is in p3*/
    ascending2(p1, p2); /* 3rd pass: in initial p2 was the smallest */
}

/**
 * @brief Reverse of ascending3()
 */
void descending3(int *p1, int *p2, int *p3)
{
    ascending3(p1, p2, p3);
    /* swap the 1st and 3rd element*/

    int temp = *p1;
    *p1 = *p3; /* 1st element is now the 3rd */
    *p3 = temp; /* 3rd element is now the 1st */
}

/**
 * @brief Returns a pointer to a sorting function based on the input character.
 */
SortFuncPtr order(char orderType) {
    SortFuncPtr funcPtr = NULL;
    if (orderType == 'A' || orderType == 'a'){
        funcPtr = &ascending3;
    }
    else if (orderType == 'D' || orderType == 'd'){
        funcPtr = &descending3;
    }
    return funcPtr;
}