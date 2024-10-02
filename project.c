#include <stdio.h>
#include <math.h>

// defining set ingredients in the coffee maker
#define BEANS 32
#define WATER 160
#define MILK 920
#define CHOCOLATE_SYRUP 120

// defining prices of different coffees
#define ESPRESSO_PRICE 3.5
#define CAPPUCCINO_PRICE 4.5
#define MOCHA_PRICE 5.5

// defining threshold limits for ingredients
#define THRESHOLD_BEANS 40
#define THRESHOLD_WATER 200
#define THRESHOLD_MILK 1150
#define THRESHOLD_CHOCOLATE_SYRUP 150

// global control variables
#define ADMIN_PASSWORD 1234 // defining admin password
double total = 0.0; // total amount of order
int choice; 
double price;

void espresso() {
    printf("|       1. Espresso       |\n");
    printf("| Price: AED %-13.2lf|\n", ESPRESSO_PRICE);
    printf("---------------------------\n");
}

void cappuccino() {
    printf("|      2. Cappuccino      |\n");
    printf("| Price: AED %-13.2lf|\n", CAPPUCCINO_PRICE);
    printf("---------------------------\n");
}

void mocha() {
    printf("|         3. Mocha        |\n");
    printf("| Price: AED %-13.2lf|\n", MOCHA_PRICE);
    printf("---------------------------\n");
}

void coffee_order() {
    printf("---------------------------\n");
    printf("|        COFFEE LIST      |\n");
    printf("---------------------------\n");
    espresso();
    cappuccino();
    mocha();

    printf("Select an item (1/2/3) or press 0 to cancel: ");
    scanf("%d", &choice);

    price = 0.0;

    if (choice == 1){
        price = ESPRESSO_PRICE;
        espresso();
        if (BEANS<8 && WATER<30) {
            printf("Unavailable due to temporarily insufficient ingredients.\n");
            return;
        }
    } else if (choice == 2) {
        price = CAPPUCCINO_PRICE;
        cappuccino();
        if (BEANS<8 && WATER<30 && MILK<70) {
            printf("Unavailable due to temporarily insufficient ingredients.\n");
            return;
        }
    } else if (choice == 3) {
        price = MOCHA_PRICE;
        mocha();
        if (BEANS< 8 && WATER<39 && MILK<160 && CHOCOLATE_SYRUP<30) {
            printf("Unavailable due to temporarily insufficient ingredients.\n");
            return;
        }
    } else if (choice == 0) {
        printf("Order canceled.\n");
        return;
    } else {
        printf("Invalid option entered. Please try again.\n");
        coffee_order();
    }
    if (choice == 1 || choice == 2 || choice == 3){
        char confirm;
        printf("Confirm purchase of coffee %d? (Y/N): ",choice);
        scanf("%c", &confirm);
        if (confirm == 'Y'|| confirm == 'y'){
            // define purchase function here
            printf("okay\n");
        } else {
            printf("Order canceled.\n");
        }
    }
    
}

void main_menu() {
    while (1) {
        printf("---------------------------\n");
        printf("|      COFFEE  MACHINE    |\n");
        printf("---------------------------\n");
        printf("| 1. Order Coffee         |\n");
        printf("| 2. Admin Mode           |\n");
        printf("| 3. Exit                 |\n");
        printf("---------------------------\n");
        
        int user_choice;
        printf("Please choose an option (1/2/3): ");
        scanf("%d",&user_choice);
        
        if (user_choice == 1){
            coffee_order();
        } else if (user_choice == 2) {
            int passcode;
            printf("Enter the admin password: ");
            scanf("%d", &passcode);
            if (passcode == ADMIN_PASSWORD) {
                // 2b steps maybe function to display admin mode capabilities
            } else {
                printf("Incorrect password entered. Please try again.\n");
            }
        } else if (user_choice == 3) {
            printf("Thank you for using the coffee machine. Hope you have a pleasant day! :)\n");
            return;
        } else {
            printf("Invalid input.\n");
        }
    }
}

int main() {
    int i;
    main_menu();
    return 0;
}
