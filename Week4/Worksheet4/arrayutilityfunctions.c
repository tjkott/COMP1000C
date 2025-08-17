/**
 * @brief arrayutilityfunctions.c = 
 */
#include <stdio.h>
#include <stdlib.h> // required for malloc() and atoi() funciton. 
#include <string.h> // REquired for strcmp() function. 
#define MAX_ARRAY_SIZE 100


/**
 * Adds up all the array elements and returns the sum, an int */ 
int sum(int arr[], int length) {
    int total = 0;
    int i;
    for (i = 0; i < length; i++){
        total += arr[i];
    }

    return total;
}

/**
 * max() - Returns the index of the largest element in the array.
 */
int max(int arr[], int length){
    if (length <= 0){
        return -1; /* Indicates empty array - error signal*/
    }
    int maxIndex = 0; /* Assume first element is max */
    int i;
    for (i = 1; i < length; i++){
        /* From 2nd element onwards, if greater than current max, update the new maxIndex*/
        if (arr[i] > arr[maxIndex]) {
            maxIndex = i;
        }
    }
    return maxIndex;
}

/**
 * reverse() - reverses the order of the array elements.
 * 
 * arr = The array of integers to be reversed. 
 * length = the number of elements in the array. 
 */
void reverse(int arr[], int length){
    int start = 0;
    int end = length -1;

    while (start < end) {
        /* swap elements at start and end indexes. */
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;

        start++; /* Move start forward*/
        end--; /* move end backwards*/
    }
}

/**
 *  convert_strings_to_ints()
 *  str_arr = initial array containing strings
 * int_arr = destination array converted to integers. 
 * length = the number of elements in the initial string array.
 */
void convert_strings_to_ints(const char* str_arr[], int int_arr[], int length){
    int i; /* loop counter*/
    for (i = 0; i < length ; i++) {
        int_arr[i] = atoi(str_arr[i]);
    }

}

/**
 * 
 */
void print_array(const char* label, int arr[], int length) {
    printf("%s: {", label);
    int i;
    for (i = 0; i < length; i++) {
        printf("%d", arr[i]);
        if (i < length - 1) {
            printf(", ");
        }
    }
    printf("}\n");
}

/**
 * to_upper_case() - converts string to upper case. 
 */
void to_upper_case(char *str){
    while (*str){ // loops as long as the ccharacter pointed to by str is not the null terminator.
        if (*str >= 'a' && *str < 'z'){
            *str = *str - ('a' - 'A'); // Compute difference in ascii values. 
        }
        str++; //Move pointer to the next character of the string.
    }
}

/**
 * @brief A temporary main function for testing the array functions.
 * Command line arguments
 * argv[1] = name of one function - sum, max or reverse
 * argv[subsequent] will be inserted into array. 
 */
int main(int argc, char* argv[]) {
    // 1. Check for the minimum number of arguments.
    // We need the program name, a command, and at least one number.
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <command> <num1> <num2> ...\n", argv[0]);
        fprintf(stderr, "Commands: 'sum', 'max', 'reverse'\n");
        return 1; // Indicate an error
    }

    int num_count = argc - 2; // The actual number of integer arguments
    int *numbers; // Declare a pointer for our dynamic array

    // Allocate memory dynamically based on the exact number of inputs.
    numbers = (int*)malloc(num_count * sizeof(int));

    // Always check if malloc was successful
    if (numbers == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return 1; // Indicate a memory allocation error
    }

    // Convert command-line arguments (from argv[2] onwards) to integers.
    convert_strings_to_ints((const char**)&argv[2], numbers, num_count);

    // Process the command from argv[1].
    char* command = argv[1];
    
    // Convert the command to uppercase to make it case-insensitive
    to_upper_case(command);

    if (strcmp(command, "SUM") == 0) {
        int result = sum(numbers, num_count);
        printf("Sum: %d\n", result);
    } else if (strcmp(command, "MAX") == 0) {
        int index = max(numbers, num_count);
        if (index != -1) {
            printf("Max value index: %d (value is %d)\n", index, numbers[index]);
        } else {
            printf("Cannot find max in an empty set of numbers.\n");
        }
    } else if (strcmp(command, "REVERSE") == 0) {
        print_array("Original", numbers, num_count);
        reverse(numbers, num_count);
        print_array("Reversed", numbers, num_count);
    } else {
        // Handle invalid commands.
        fprintf(stderr, "Error: Unknown command '%s'.\n", argv[1]);
        fprintf(stderr, "Available commands: 'sum', 'max', 'reverse'\n");
        free(numbers); // Free memory even on error
        return 1; // Indicate an error
    }

    // Free the dynamically allocated memory before exiting
    free(numbers);

    return 0; // Success
}
