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
            printf("show: %d",avail_beans);
            avail_water -= WATER;
        } else if (choice == 2) {
            avail_beans -= BEANS;
            avail_water -= WATER;
            avail_milk -= CAPPUCCINO_MILK;
        } else if (choice == 3) {
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
        total_amount += price;
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

void admin_mode(){
    while (1){
        printf("------------------------------\n");
        printf("|         ADMIN  MODE        |\n");
        printf("------------------------------\n");
        printf("| 1 - View Sales             |\n");
        printf("| 2 - Replenish Ingredients  |\n");
        printf("| 3 - Update Pricing         |\n");
        printf("| 0 - Exit Admin Mode        |\n");
        printf("------------------------------\n");

        int admin_choice;
        printf("Please choose an option (0/1/2/3): ");
        scanf("%d",&admin_choice);

        if (admin_choice == 1){
            printf("---------------------------\n");
            printf("|        INGREDIENTS      |\n");
            printf("---------------------------\n");
            printf(" Beans: %d\n",avail_beans);
            printf(" Water: %d\n",avail_water);
            printf(" Milk: %d\n",avail_milk);
            printf(" Chocolate Syrup: %d\n",avail_syrup);
            printf("---------------------------\n");
            printf(" Total sale amount: %1.2lf \n",total_amount);
            printf("---------------------------\n");

            char update_amt;
            printf("Would you like to reset the total sale amount to zero? (Y/N): ");
            scanf("%s",&update_amt);

            if (update_amt == 'Y' || update_amt == 'y'){
                total_amount = 0.0;
                printf("Total sale amount resetted. Please collect the money from the machine.\n");
                continue;
            } else {
                continue;
            }
        } else if (admin_choice == 2){
            printf("Old quantity of beans : %d\n",avail_beans);
            printf("Old quantity of water : %d\n",avail_water);
            printf("Old quantity of milk : %d\n",avail_milk);
            printf("Old quantity of chocolate syrup : %d\n",avail_syrup);
            avail_beans = rand()%((20*THRESHOLD_BEANS)-THRESHOLD_BEANS + 1) + THRESHOLD_BEANS;
            avail_water = rand()%((20*THRESHOLD_WATER)-THRESHOLD_WATER + 1) + THRESHOLD_WATER;
            avail_milk = rand()%((20*THRESHOLD_MILK)-THRESHOLD_MILK + 1) + THRESHOLD_MILK;
            avail_syrup = rand()%((20*THRESHOLD_CHOCOLATE_SYRUP)-THRESHOLD_CHOCOLATE_SYRUP + 1) + THRESHOLD_CHOCOLATE_SYRUP;
            printf("New quantity of beans : %d\n",avail_beans);
            printf("New quantity of water : %d\n",avail_water);
            printf("New quantity of milk : %d\n",avail_milk);
            printf("New quantity of chocolate syrup : %d\n",avail_syrup);
        } else if (admin_choice == 3){
            printf("---------------------------\n");
            printf("|        COFFEE LIST      |\n");
            espresso();
            cappuccino();
            mocha();

            int choice4;
            double new_price;
            printf("Which coffee price would you like to update? (1/2/3): ");
            scanf("%d",&choice4);
            if (choice4 == 1){
                espresso();
                printf("Please enter the updated price: ");
                scanf("%lf",&new_price);
                ESPRESSO_PRICE = new_price;
                printf("Price updated successfully!\n");
                espresso();
            } else if (choice4 == 2){
                cappuccino();
                printf("Please enter the updated price: ");
                scanf("%lf",&new_price);
                CAPPUCCINO_PRICE = new_price;
                printf("Price updated successfully!\n");
                cappuccino();
            } else if (choice4 == 3){
                mocha();
                printf("Please enter the updated price: ");
                scanf("%lf",&new_price);
                MOCHA_PRICE = new_price;
                printf("Price updated successfully!\n");
                mocha();
            } else {
                printf("Invalid option entered. Please try again.\n");
                continue;
            }
        } else if (admin_choice == 0){
            printf("Thank you for using the operator mode.\n");
            break;
        } else {
            printf("Invalid option entered. Please try again. \n");
            continue;
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
                admin_mode();
            } else {
                printf("Incorrect password entered. Please try again.\n");
            }
        } else if (user_choice == 3) {
            printf("Thank you for using the coffee machine. Hope you have a pleasant day! :)\n");
            break;
        } else {
            printf("Invalid input.\n");
            continue;
        }
    }
}

int main() {
    int i;
    main_menu();
    return 0;
}