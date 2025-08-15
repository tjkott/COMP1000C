/**
 * @file macros.c
 * @brief Declares only the functions that will be available to other parts of the program as well.
 * ascending2() is not included as it is a static function. 
 */
#ifndef ORDER_H /* Header guard to prevent multiple inclusions during compilation. */
#define ORDER_H 
#include <stdio.h>

/* Define a void function type called 'SortFuncPtr'.
It is a pointer to any function that takes 3 integer pointers as arguments and returns void. */
typedef void(*SortFuncPtr)(int *p1, int *p2, int *p3);

void ascending3(int *p1, int *p2, int *p3);
void descending3(int *p1, int *p2, int *p3);

SortFuncPtr order(char orderType); /* */

#endif
