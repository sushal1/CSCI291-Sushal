#include <stdio.h>

int balance = 1000;
int transactions[] = {200,-150,-500,-400,-50,-200,300}; //sample array

int length_transactions;

int main() {
    length_transactions = sizeof(transactions)/sizeof(transactions[0]);
    int tobeprocessed[length_transactions]; //creating array
    int j = 0;
    for (int i = 0;i<length_transactions;i++) {
        if (balance == 0){
            printf("Balance: 0 AED. No further transactions will be processed.\n");
            tobeprocessed[j++] = transactions[i];
            break;
        }
        else {
            if (transactions[i]<0 && -transactions[i]>balance) {
                printf("Transaction invalid due to insufficient balance.\n");
                tobeprocessed[j++] = transactions[i];
            } else {
                balance+=transactions[i];
            }
        }
    }
    
    printf("Balance: %d\n",balance);
    printf("Unprocessed transactions: \n");
    for (int k = 0; k<j;k++){
        printf("%d   ",tobeprocessed[k]);
    }
    printf("\n");
    return 0;
}