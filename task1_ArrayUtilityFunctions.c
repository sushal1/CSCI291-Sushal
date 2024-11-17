//--- TASK 1: ARRAY UTILITY FUNCTIONS ---

// Libraries in use
#include <stdio.h>
#include <stdbool.h> 

// Setting values for SIZE, nRows, nCols
#define SIZE 24
#define nRows 8
#define nCols 3

// PROTOTYPES
void print_array(int array[], int length); //pre-declared function for printing array
void print_matrix(int mat[][nCols], int rows); //pre-declared function for printing matrix

void set_array(int arr[], int length); //prototype for function for setting array
bool isValid(int arr[], int length, int pos); // prototype for function for checking if indices are valid
void remove_element(int arr[], int length, int pos); //prototype for function for removing an element from array
void insert_element(int arr[], int length, int pos, int value); //prototype for function for inserting element into array
void reshape(int arr[], int length, int arr2d[nRows][nCols]); //prototype for function for copying elements from array to array2d
void trans_matrix(int arr2d[nRows][nCols]); //prototype for function for printing columns of matrix
bool found_duplicate(int arr[], int length); //prototype for function that checks for duplicates in array

// initialising code - FUNCTION CALLS
int main()
{
   int arr[SIZE]; //initialising array 'arr' having pre-defined SIZE
   int arr2d[nRows][nCols]; //initialising array 'arr2d' having pre-defined rows & columns
     
   //Call to different functions

   //Setting value of element to index
   set_array(arr, SIZE); //calling the function that sets the array

   //Printing initial array
   printf("Array after setting it: \n");
   print_array(arr,SIZE); //calling the function that prints the array

   //Removing one element
   int remove = 5; 
   remove_element (arr, SIZE, remove); 
   printf("Array after removing element at position %d: \n", remove);
   print_array(arr, SIZE-1);

   // Inserting an element
   int new_element = 69;
   int insert = 5; 
   insert_element(arr, SIZE-1, insert, new_element); 
   printf("Array after inserting %d at position %d: \n", new_element,insert);
   print_array(arr, SIZE); 
   
   reshape(arr, SIZE, arr2d); //calling the function that reshaps arr to arr2d
   printf("Array2D after reshaping: \n");
   print_matrix(arr2d, nRows);
   
   printf("Column-wise print of arr2d: \n");
   trans_matrix(arr2d); //printing matrix columns of arr2d

   //Searching for duplicates in arr
   found_duplicate(arr,SIZE);

   return 0;
}

// printing the array
void print_array(int array[], int length){
   for(int i=0;i<length; i++) // traverses through array
      printf("array[%d]= %d\n", i, array[i]); // printing element by element
}

// printing the matrix (rows)
void print_matrix(int mat[][nCols], int rows){ 
   for(int i=0;i<rows; i++){ // traverses through rows
    for(int j=0;j<nCols; j++) // traverses through columns
         printf("mat[%d][%d]= %d\n", i,j, mat[i][j]); // prints element by element
    puts(""); // new line  
   }   
}

//FUNCTION DEFINITIONS

//making an array
void set_array(int arr[], int length) {
   for (int i = 0; i<length; i++){ // traverses through array
      arr[i] = i; // setting first element as 0, 1, 2 etc
   }
}

// isValid()
bool isValid(int arr[],int length, int pos) {
    if (pos >= 0 && pos < length) { 
        return true; // returns true if position is in range of array length
        
    }
    else {
        return false; // otherwise false
    }
}

//remove_element()
void remove_element(int arr[], int length, int pos) {
   if (isValid(arr,length,pos)) { // checking validity of position
        for (int i = pos; i < length - 1; i++) { // goes through array from given position
            arr[i] = arr[i + 1]; // sets element at position as next element and so on
      }
   }
   else {
      printf("Incorrect array index entered.\n"); // handling error for invalid index
   }
}

//insert_element()
void insert_element(int arr[], int length, int pos, int value) {
   if (isValid(arr,length,pos)) { // checking validity of index
      for (int i = length; i > pos; i--) { // goes through array from last element of array till position
         arr[i] = arr[i - 1]; // sets elements after position as the element from pos and so on
      }
      arr[pos] = value; // sets element at pos as given value
   } else {
      printf("Incorrect array index entered. \n"); // handling error for invalid index
   }
}

//reshape()
void reshape(int arr[], int length, int arr2d[nRows][nCols]) {
   if (length == (nRows*nCols)){ // checks if length given is equal to prod of rows and cols
      int position = 0; // variable for position
      for (int i = 0; i< nRows; i++) { // outer loop for rows
         for (int j = 0; j< nCols; j++) { // inner loop for cols
            if (position < length) { // as long as position is less than length of array
               arr2d[i][j] = arr[position]; // first element of matrix will be 0, followed by arr[0][1] = 1 and so on
               position++; // position incremented
            }
         }
      }
   } else{
      printf("Array length does not match the product of rows & columns of the 2D array.\n"); // handling error for invalid length
   }
}

void trans_matrix(int arr2d[nRows][nCols]) {
   for (int j = 0; j < nCols; j++) { // outer loop goes through columns
      for (int i = 0; i < nRows; i++) { // inner loop goes through rows
         printf("%d ", arr2d[i][j]); // printing the array element by element such that the matrix is transposed
      }
      printf("\n"); // new line
   }
}

//searching for duplicates
bool found_duplicate(int arr[], int length) { 
   for (int i = 0; i < length; i++) {  // goes through array from start
      for (int j = i+1; j< length; j++){ // goes through array from next element
         if (arr[i] == arr[j]) { // checks if elements are equal
            printf("Duplicates found in array. \n"); // if duplicates found
            return true; // returning true
         }
      }
   }
   printf("No duplicates found. \n"); // if duplicates not found
   return false; // returning false
}


