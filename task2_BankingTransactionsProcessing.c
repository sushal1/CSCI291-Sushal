// --- TASK 2: BANKING TRANSACTIONS PROCESSING ---

// LIBRARY HEADERS
#include <stdio.h>

// GLOBAL VARIABLES
int balance = 1000; // initial balance
int transactions[] = {200,-150,-500,-400,-50,-200,300}; // sample array from qn
int length_transactions; // variable for length of transactions array

// MAIN FUNCTION
int main() {
    length_transactions = sizeof(transactions)/sizeof(transactions[0]); // calculating length of transactions array
    int tobeprocessed[length_transactions]; // creating array for unprocessed transactions w same length as transactions
    int j = 0; // initialising variable

    for (int i = 0; i<length_transactions; i++) { // loop goes through array length
        // if balance is zero at any point
        if (balance == 0){
            printf("Balance: 0 AED. No further transactions will be processed.\n");
            tobeprocessed[j++] = transactions[i]; // storing unprocessed transaction
            break; // stopping transactions
        }
        // if balance is not zero
        else {
            if (transactions[i]<0 && -transactions[i]>balance) { // if withdrawal is more than balance
                printf("Transaction invalid due to insufficient balance.\n");
                tobeprocessed[j++] = transactions[i]; // storing unprocessed transaction
            } else {
                balance+=transactions[i]; // adding current transaction to balance
            }
        }
    }
    
    printf("Balance: %d\n",balance); // printing balance

    printf("Unprocessed transactions: \n"); 
    for (int k = 0; k<j;k++){ // loop will run for the value of j
        printf("%d   ",tobeprocessed[k]); // printing array of unprocessed transactions element by element
    }
    printf("\n"); // printing new line

    return 0;
}