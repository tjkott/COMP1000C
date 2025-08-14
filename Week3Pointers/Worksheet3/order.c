#include <stdio.h>
#include "ORDER_H"

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
