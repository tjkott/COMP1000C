#include<stdio.h>
int main(){
    int number1 = 100;
    int number2 = 200;
    int * p = &number1; /* pointer to address number1 */
    printf("Number before modfication is %d and %d\n", number1, number2);

    *p = 5000; /* dereference pointer to change value of number1 */
    printf("Number after modifying number1 is %d\n", number1);

    p = &number2; /* now point to address of number2 */
    *p = 6000; /* dereference pointer to change value of number2 */
    printf("Number after modifying number2 is %d\n", number2);

    p = &number1; /* point back to number1 */
    *p = 0; /* dereference pointer to change value of number1 */

    int ** q = NULL; /* pointer to pointer */
    return 0;

}

void doubleIt(int * a);

int main(int * a){
    int number = 100;

    doubleIt(&number);

    printf("Number is %d\n", number);

    return 0;

}

void doubleIt(int * a){
    (*a) = (*a) * 2;
}