#include<stdio.h>
#include<stdlib.h>
#include"calculation.h"
#include"calculation.h"
#include"io.h"


#define SQUARE(x) ((x)*(x)) //reason for so many brackets around is just to be safe. 

int main(){
    int num1, num2;

    num1 = enterInt();
    num2 = enterInt();

    printf("%d + %d = %d\n", num1, num2, addition(num1, num2));
    printf("%d - %d = %d\n", num1, num2, subtraction(num1, num2));   
}
