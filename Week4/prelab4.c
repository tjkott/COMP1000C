#include <stdio.h>
#include <stdlib.h>

/* 1. Array declarations:
*  Explain the meaning of each of the following.

(a) int a[14];
    Array named 'a' that can hold 14 elements. 
(b) double b[] = {3.3, 0.0, 1.1, 2.2};
    Declares an array named b that contains elements of the type double/floats. 
    
(c) float c[5][10]; 
    2 dimensional array that is 5 ros and 10 columns. 

(d) int *d[10];
    Array named d of size 10 elements. Each element of this array is a pinter to an integer. 
    Each address is expected to point to an int value. 
(e) void **e[3][4];
    2 dimensional array named e with 3 rows and 4 columns.
    Each element is a pointer to a pointer. 
    void * would be a generic pointer that can point to any type of data. 
    void** is a pointer to one of these pointers. 

(f) char s[] = "Hello";
    Array named s is initialised containing the string "Hello".
    Size of s is 6 bytes including the null terminator character '\0'.
(g) char *s = "Hello";
    Pointer named s that points to character string "Hello".

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
* (b) c = Pointer to a first element on the array c. = c[0] 
* (c) c[2] = & of the 1st element of the 3 row
* (d) c + 2 = c + 2 is a pointer to the 3rd row of the array. 
* (e) *(c + 2) = dereferenced. Pointer to an integer pointing to the 1st element of the 3rd row. Same as c[2]
* (f) c[2] + 1 = & of the 2nd element in the 3rd row.
* (g) *(c[2] + 1) = 
* (h) *(*(c + 1) + 2) = 
* (i) c[0][6] 
* (j) *((c + 2) + 1) = 
*/

/**
 * Malloced Arrays
 */
/*
* (a) An array of 25 integers
* (b) an Array of 25 pointer to floats. 
* (c) an array of 25 pointers, each pointing to an array of 15 chars.
*/

int main(){
    /* Declare a pointer to an int.*/
    int *intArray;

    /* Allocate memory for 25 ints.*/
    intArray = (int*)malloc(25 * sizeof(int));

    /* Always check if malloc was successful*/
    if (intArray == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    /* Free allocated memory */
    free(intArray);
    return 0;
}

int main(){
    /* Pointer to a pointer to a float*/
    float **floatPtrArray;

    floatPtrArray = (float**)malloc(25 * sizeof(float*));

    if (floatPtrArray == NULL) {
        printf("memory allocation failed for pointer array!");
        return 1;
    }

    free(floatPtrArray);


   return 0;
}

/* Array of 25 pointers, each pointing to array of 15 chars*/
int main(){
    /* Pointer to a pointer to a char*/
    char **charPtrArray;
    int i;

    /* Allocate memory for 25 pointers*/
    charPtrArray = (char**)malloc(25 * sizeof(char*));

    /* Check if allocation was successful*/
    if (charPtrArray == NULL) {
        printf("Memory allocation failed for pointer array!");
        return 1;
    
    }

    /* Allocate memory for each of the 25 15-char string arrays. */
    for (i = 0; i < 25; i++){
        charPtrArray[i] = (char*)malloc(15 *sizeof(char));

        /* check if each sub-allocation is succesful*/
        if (charPtrArray[i] == NULL){
            printf("Memory allocation failed for char array at index %d", i);
            /* if one fails, free what was already allocated*/
            for (int j = 0; j < 1; j++){
                free(charPtrArray[j]);
            }
            free(charPtrArray)
            return 1;
        }
    }
        /* Free the memory in reverse order of allocation*/
        for (i = 0; i < 25; i++) {
            free(charPtrArray[i]);
        }
        free(charPtrArray);
        return 0;
    }