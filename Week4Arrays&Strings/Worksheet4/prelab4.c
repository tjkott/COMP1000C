#include <stdio.h>
#include <stdlib.h>

/* 1. Array declarations:
*  Explain the meaning of each of the following.

(a) int a[14];
    Array named 'a' that can hold 14 elements. 
(b) double b[] = {3.3, 0.0, 1.1, 2.2};
    
(c) float c[5][10]; (d) int *d[10];
(e) void **e[3][4];
(f) char s[] = "Hello";
(g) char *s = "Hello";

*/


int a[] = {10, 15, 20, 25};
int b[] = {50, 60, 70, 80};

int* x[] = {a, b}; /* */
int* y[] = {a + 2, b + 3};

int* p; /* pointer p */
int* q;
int** r;

p = a; 
q = y[1]; /* */
r = &q; 

*p = &p[3] - y[0];
r[0][1] = **r - y[0][1];


/* 3. Array expressions*/
int c[5][4] = {{ 1, 2, 3, 4}, 
                {5, 6, 7, 8}, 
                { 9, 10, 11, 12}, 
                {13, 14, 15, 16},
                {17, 18, 19, 20}};

/*
* (a) c[2][1] = 10
* (b) c = 
* (c) c[2] = & of the 1st element of the 3 row
* (d) c + 2 = & of the pointer to the 1st element
* (e) *(c + 2) = dereferenced. c[2]
* (f) c[2] + 1 = & of the 2nd element in the 3rd row.
* (g) *(c[2] + 1) = 
* (h) *(*(c + 1) + 2) = */