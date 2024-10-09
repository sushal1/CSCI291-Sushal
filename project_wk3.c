#include <stdio.h>
#include <math.h>

#define ADMIN_PASSWORD 1234 // defining admin password

// defining low threshold limits for ingredients
#define THRESHOLD_BEANS 16
#define THRESHOLD_WATER 80
#define THRESHOLD_MILK 320
#define THRESHOLD_CHOCOLATE_SYRUP 60

// defining quantity requirements
#define BEANS 8 // all coffees need same amount of beans
#define WATER 30 // for espresso & cappuccino
#define MOCHA_WATER 39 
#define CAPPUCCINO_MILK 70 
#define MOCHA_MILK 160
#define CHOCOLATE_SYRUP 30

// declaring prices of different coffees
double ESPRESSO_PRICE = 3.5;
double CAPPUCCINO_PRICE = 4.5;
double MOCHA_PRICE = 5.5;

// available quantities of ingredients in the coffee maker
int avail_beans = 56;
int avail_water = 280;
int avail_milk = 1120;
int avail_syrup = 210;

// variables for payment collection
double total_amount = 0.0; // total amount of order
int choice; 
double price;
double paid;

void espresso() {
    printf("---------------------------\n");
    printf("|       1. Espresso       |\n");
    printf("| Price: AED %-13.2lf|\n", ESPRESSO_PRICE);
    printf("---------------------------\n");
}

void cappuccino() {
    printf("---------------------------\n");
    printf("|      2. Cappuccino      |\n");
    printf("| Price: AED %-13.2lf|\n", CAPPUCCINO_PRICE);
    printf("---------------------------\n");
}

void mocha() {
    printf("---------------------------\n");
    printf("|         3. Mocha        |\n");
    printf("| Price: AED %-13.2lf|\n", MOCHA_PRICE);
    printf("---------------------------\n");
}

void payment() {
    if (price > paid) {
        printf("Please enter the coins one at a time (0.5/1). \n");
        double coins;
        printf("Enter coin: ");
        scanf("%lf",&coins);
        
        if (coins == 0.5 || coins == 1){
            printf("Coin accepted.\n");
            paid+=coins;
            payment();
        } else {
            printf("Invalid coin entered. Please collect the coin and insert a valid coin.\n");
            payment();
        }
    } else {
        double change;
        change = paid - price;
        if (change > 0){
            printf("Please collect your change of AED %-8.2lf\n",change);
        }
        if (choice == 1) {
            avail_beans -= BEANS;
            avail_water -= WATER;
        } else if (choice == 2) {
            avail_beans -= BEANS;
            avail_water -= WATER;
            avail_milk -= CAPPUCCINO_MILK;
        } else if (choice == 2) {
            avail_beans -= BEANS;
            avail_water -= MOCHA_WATER;
            avail_milk -= MOCHA_MILK;
            avail_syrup -= CHOCOLATE_SYRUP;
        }
        
        if (avail_beans <= THRESHOLD_BEANS) {
            printf("Message to operator: Quantity of beans is less than/equal to minimum.\n");
        } else if (avail_water <= THRESHOLD_WATER) {
            printf("Message to operator: Quantity of water is less than/equal to minimum.\n");
        } else if (avail_milk <= THRESHOLD_MILK) {
            printf("Message to operator: Quantity of milk is less than/equal to minimum.\n");
        } else if (avail_syrup <= THRESHOLD_CHOCOLATE_SYRUP) {
            printf("Message to operator: Quantity of chocolate syrup is less than/equal to minimum.\n");
        }
        
        printf("Order placed successfully. Please collect your coffee from below.\n");
        total_amount += paid;
        paid = 0.0;
    }
}

void coffee_order() {
    printf("---------------------------\n");
    printf("|        COFFEE LIST      |\n");
    espresso();
    cappuccino();
    mocha();

    printf("Select an item (1/2/3) or press 0 to cancel: ");
    scanf("%d", &choice);

    price = 0.0;

    if (choice == 1){
        price = ESPRESSO_PRICE;
        espresso();
        if (avail_beans<BEANS && avail_water<WATER) {
            printf("Unavailable due to temporarily insufficient ingredients.\n");
            return;
        }
    } else if (choice == 2) {
        price = CAPPUCCINO_PRICE;
        cappuccino();
        if (avail_beans<BEANS && avail_water<WATER && avail_milk<CAPPUCCINO_MILK) {
            printf("Unavailable due to temporarily insufficient ingredients.\n");
            return;
        }
    } else if (choice == 3) {
        price = MOCHA_PRICE;
        mocha();
        if (avail_beans<BEANS && avail_water<WATER && avail_milk<MOCHA_MILK && avail_syrup<CHOCOLATE_SYRUP) {
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
    
    char confirm;
    printf("Confirm purchase of coffee %d? (Y/N): ",choice);
    scanf("%s", &confirm);
    
    if (confirm == 'Y'|| confirm == 'y'){
        payment();
    } else {
        printf("Order canceled.\n");
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
