#include <stdio.h>
#include <stdlib.h>

/*Fucntion to the print state of the variables*/
void initialise(int* a_ptr, int* b_ptr, int** x_ptr, int** y_ptr, int*** s_ptr, int*** t_ptr) {
    *a_ptr = 2;
    *b_ptr = 10;
    *x_ptr = NULL;
    *y_ptr = NULL;
    *s_ptr = NULL;
    *t_ptr = NULL;
}

void print_state(const char* title, int a, int b) {
    printf("--- %s ---\n", title);
    printf("Initial values: a = %d, b = %d\n", a, b);
}

int main(void)
{
    /* Variables declaration*/
    int a, b;
    int* x;
    int* y;
    int** s;
    int** t;

    /* Case (a)*/
    initialise(&a, &b, &x, &y, &s, &t);
    x = &a;
    *x = b;
    print_state("After x = &a; *x = b;", a, b);

    /* Case (b)*/
    initialise(&a, &b, &x, &y, &s, &t);
    s = &x;
    x = &a;
    y = &b;
    t = s;
    **t = **t * *y; /* dereference pointer to change value of number1 */

    print_state("After Case (b)", a, b);
    /* Case (c)*/
    initialise(&a, &b, &x, &y, &s, &t);
    int i;
    x = &a;
    y = &b;
    for(i = 1; i <= *x; i++)
    {
        *y = *y + 1;
    }
    print_state("After Case (c)", a, b);

    /* Case (d)*/
    initialise(&a, &b, &x, &y, &s, &t);
    x = &b;
    y = &a;
    t = &y;
    *t = x;
    if(**t > 5) {
        s = t;
    
    }
    else {
        s = &x;
    }
    **s = **s / *x;
    print_state("After Case (d)", a, b);

    /* Case (e)*/
    initialise(&a, &b, &x, &y, &s, &t);
    x = (int*)malloc(sizeof(int));
    y = (int*)malloc(sizeof(int));
    *x = 8;
    *y = 8;
    if(x == y) {
        a = *x + *y;
    }
    if(*x == *y) {
        b = *y;
    }
    print_state("After Case (e)", a, b);
    free(x);
    free(y);
    x = NULL; /* Avoid dangling pointer */
    y = NULL; /* Avoid dangling pointer */
    
    /* Case (f)*/
    initialise(&a, &b, &x, &y, &s, &t);
    s = (int**)malloc(sizeof(int*));
    *s = (int*)malloc(sizeof(int));
    t = s;
    x = *t;
    **t = b;
    s = (int**)malloc(sizeof(int*));
    *s = &a;
    **s = *x;
    print_state("After Case (f)", a, b);
    free(*s);
    free(s);
    s = NULL; /* Avoid dangling pointer */
    t = NULL; /* Avoid dangling pointer */

    return 0;
}