/* Question 1
At least 1 problem. 
Passing by value = affect the original variables. 
Solution: passing by reference = */
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* Question 2 - Is memory allocation done correctly. */
// 1D array
//2D array
void createMatrix(int * size) {
    int row = size[0];
    int col = size[1];
    int ** matrix = (int **) malloc(row * sizeof(int *));;
    int i, j;
    // 2. Loop and allocate memory for each individual row
    for(i = 0; i < row; i++) { // Not enoguh free
        matrix[i] = (int *) malloc(col * sizeof(int));
        for(j=0; j < col; j++) {
            matrix[i][j] = 0;
        }
    }
    // 1. Free each individual row that was allocated inside the loop
    for(i = 0; i < row; i++) {
        free(matrix[i]);
    }
    // 2. Free the array of row pointers
    free(matrix);
    // 3. Don't free an array that isn't malloc'ed. 
}

/*Question 4*/
void oddOrEven(int *arr, int length) {
    int i;
    int even = 0;
    int odd = 0;
    for (i = 0; i < length; i++) {
        if (arr[i] % 2 == 0) {
            even = even + 1;
        } else {
            odd = odd + 1;
        }
    }
    if (even > odd) {
        printf("Even\n");
    } else {
        printf("Odd\n");
    }
}
void convertUpper(char *str) {
    while(*str != '\0') { // as long as char is not NULL. 
        if (*str >= 'a' && *str <= 'z') { // if char is lower case. 
            *str = *str - 32;
        }
    }
    str = str + 1; // move the pointer to the next char in the string. 
}