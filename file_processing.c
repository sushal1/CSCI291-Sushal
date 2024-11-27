// --- Question #1: File Processing --- //

// LIBRARIES TO INCLUDE
#include <stdio.h>

// MAIN FUNCTION
int main() {
    // Variables Needed
    FILE *input_file; // initializing a pointer to store the input file
    FILE *output_file; // initializing a pointer to store the input file
    char file_content[1000]; // array to read content of file
    float value; // variable to read valid characters
    int invalid_character = 0; // variable to count the number of invalid characters

    // Opening the input file
    // update file name here to read from file
    input_file = fopen("data.txt", "r"); // using fopen() in read mode
    if (input_file == NULL) { // if the file does not exist
        printf("Error in opening input file.\n"); // error handling statement
        return 1;
    }
    printf("The input file has been opened.\n"); // confirming to the user that file is open

    // Opening the output file
    output_file = fopen("output.txt", "w"); // using fopen() in write mode
    if (output_file == NULL) { // if the file was not opened
        printf("Error in creating output file.\n"); // error handling statement
        fclose(input_file); // closing the input file in case of error
        return 1;
    }
    printf("The output file has been created.\n");

    // Loop to traverse through file
    while (fscanf(input_file, "%s", file_content) != EOF) { // reading strings from file till the end of the file
        if (sscanf(file_content, "%f", &value) == 1) { // reading characters from string
            fprintf(output_file, "%.1f\n", value); // printing the characters from file
        } else {
            invalid_character++; // incrementing this variable for invalid characters
        }
    }
    // printing the number of invalid values
    printf("Number of invalid float values: %d\n", invalid_character); // printing the number of invalid values

    // Closing the input and output file
    fclose(input_file); // closing the input file
    fclose(output_file); // closing the output file

    return 0;
}