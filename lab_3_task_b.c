#include <stdio.h>

int main() {
    int balance = 1000; //initial balance
    int transactions[] = {200, -150, -500, -400, -50, -200, 300}// transactions given in the question
    int tobeprocessed[7]; //array for unprocessed transactions
    int tobeprocessed_count = 0; //number of unprocessed transactions 
    for (int i = 0; i < 7; i++) {
        if (transactions[i] < 0 && -transactions[i] > balance) {
            printf("Transaction %d is invalid   withdrawal of %d, insufficient balance\n",i, -transactions[i]);
            tobeprocessed[tobeprocessed_count++] = transactions[i];
        } else {
            balance += transactions[i];
            if (balance == 0){
                printf("The balance has reached 0,Terminating further transactions\n");
                break;
            }
        }
    }
     printf("Final balance: %d AED\n", balance);
}