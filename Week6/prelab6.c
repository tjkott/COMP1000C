/**
 * Pre lab 6
*/

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Question 1: Show what the output would be from the following printf statements:
 * 
 */
printf("---%-4d---%+4d---", 23, 46);
/*Output: ----  23--- +46---
%4d reserves a field of 4 characters. 
%+4d reserves a 4 character field for 
*/

printf("x=%6.3f, y=%6.3f", 1.23, 216.0);
/* Output: x= 1.230, y=216.000
Reserves 6 characters and displays number with exactly 3 digits after the decimal point. 
*/

/**
 * @brief Question 2 : Show what the output would be from the following printf statements:
 * 
 */
//(a) The name of a species. 
char genus[50]; // This declares an array of 50 characters
char species[50]; //
scanf("%s %s", genus, species); // %s tells to skip over whitespace between 1st and 2nd strings

//(b) Time of day in the format "hours:minutes:seconds ampm"
int hours, minutes, seconds;
char ampm[3] //2 characters for am, pm + null character. 
scanf("%d:%dL%d %s", &hours, &minutes, &seconds, ampm)
// %d is used to read integer values for hours, minute s and seconds. 
//%s reads the final ampm string. 