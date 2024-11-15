// --- COFFEE MAKER SIMULATOR ---

// HEADERS
#include <stdio.h>
#include <math.h>

// DEFINITIONS OF CONSTANTS

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

// FUNCTION PROTOTYPES
void espresso(); // for displaying details of espresso
void cappuccino(); // for displaying details of cappuccino
void mocha(); // for displaying details of mocha
void payment(); // for handling payment of coffee
void coffee_order(); // for ordering coffee
void admin_mode(); // for the admin mode
void main_menu(); // for the main menu

// DECLARATIONS OF VARIABLES

// declaring prices of different coffees
double ESPRESSO_PRICE = 3.5;
double CAPPUCCINO_PRICE = 4.5;
double MOCHA_PRICE = 5.5;

// available quantities of ingredients in the coffee maker
int avail_beans = 56;
int avail_water = 280;
int avail_milk = 1120;
int avail_syrup = 210;

// global variables for payment collection
double total_amount = 0.0; // total amount of order 
int choice; // for choosing the type of coffee
double price; // for the price of the coffee
double paid; // for the amount paid

// FUNCTION DEFINITIONS

// FUNCTION FOR DISPLAYING DETAILS OF ESPRESSO
void espresso() {
    printf("---------------------------\n");
    printf("|       1. Espresso       |\n");
    printf("| Price: AED %-13.2lf|\n", ESPRESSO_PRICE);
    printf("---------------------------\n");
}

// FUNCTION FOR DISPLAYING DETAILS OF CAPPUCCINO
void cappuccino() {
    printf("---------------------------\n");
    printf("|      2. Cappuccino      |\n");
    printf("| Price: AED %-13.2lf|\n", CAPPUCCINO_PRICE);
    printf("---------------------------\n");
}

// FUNCTION FOR DISPLAYING DETAILS OF MOCHA
void mocha() {
    printf("---------------------------\n");
    printf("|         3. Mocha        |\n");
    printf("| Price: AED %-13.2lf|\n", MOCHA_PRICE);
    printf("---------------------------\n");
}

// FUNCTION FOR MAKING PAYMENT OF COFFEE ORDER
void payment() {
    // if the price is more than the amount paid
    if (price > paid) {
        printf("Please enter the coins one at a time (0.5/1). \n");
        double coins; // temporary variable for checking user's input
        printf("Enter coin: "); // asking user to enter coins
        scanf("%lf",&coins); // storing the user's input
        
        // if the user has entered the correct coin
        if (coins == 0.5 || coins == 1){
            printf("Coin accepted.\n"); // coin is accepted
            paid+=coins; // the coin inserted is added to the amount paid
            printf("Amount paid: %-.2lf\n",paid);
            payment(); // recursing to the beginning of the payment function
            
        // for any other input
        } else {
            printf("Invalid coin entered. Please collect the coin and insert a valid coin.\n"); // coin is rejected
            payment(); // recursing to the beginning of the payment function
        }
        
    // if the amount paid is more than or equal to the price    
    } else {
        double change; // initialising a change variable
        change = paid-price; // for amount paid more than price
        if (change > 0){
            printf("Please collect your change of AED %-8.2lf\n",change); // printing change amount if any
        }
        
        // depletion of ingredients for the chosen coffee
        if (choice == 1) {
            avail_beans -= BEANS; 
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
        // checking for low ingredient quantities
        if (avail_beans <= THRESHOLD_BEANS) {
            printf("Message to operator: Quantity of beans is less than/equal to minimum.\n");
        } else if (avail_water <= THRESHOLD_WATER) {
            printf("Message to operator: Quantity of water is less than/equal to minimum.\n");
        } else if (avail_milk <= THRESHOLD_MILK) {
            printf("Message to operator: Quantity of milk is less than/equal to minimum.\n");
        } else if (avail_syrup <= THRESHOLD_CHOCOLATE_SYRUP) {
            printf("Message to operator: Quantity of chocolate syrup is less than/equal to minimum.\n");
        }
        
        printf("Order placed successfully. Please collect your coffee from below.\n"); // asking the user to collect coffee
        total_amount += price; // appending the price to the total sales
        paid = 0.0; // resetting the payment variable
    }
}

// FUNCTION FOR ORDERING COFFEE
void coffee_order() {
    // displaying the coffee options
    printf("---------------------------\n");
    printf("|        COFFEE LIST      |\n");
    espresso();
    cappuccino();
    mocha();

    printf("Select an item (1/2/3) or press 0 to cancel: ");
    scanf("%d", &choice); // storing the user's choice

    price = 0.0; // resetting the temporary price variable to zero
    
    // for espresso
    if (choice == 1){
        price = ESPRESSO_PRICE; // setting the temporary price variable to the price of the coffee
        espresso(); // displaying the coffee details
        // if the available ingredients are insufficient
        if (avail_beans<BEANS || avail_water<WATER) {
            printf("Unavailable due to temporarily insufficient ingredients.\n");
            return; // returning to main menu
        }
        
    // for cappuccino
    } else if (choice == 2) {
        price = CAPPUCCINO_PRICE; // setting the temporary price variable to the price of the coffee
        cappuccino(); // displaying the coffee details
        // if the available ingredients are insufficient
        if (avail_beans<BEANS || avail_water<WATER || avail_milk<CAPPUCCINO_MILK) {
            printf("Unavailable due to temporarily insufficient ingredients.\n");
            return; // returning to main menu
        }
        
    // for mocha
    } else if (choice == 3) {
        price = MOCHA_PRICE; // setting the temporary price variable to the price of the coffee
        mocha(); // displaying the coffee details
        // if the available ingredients are insufficient
        if (avail_beans<BEANS || avail_water<WATER || avail_milk<MOCHA_MILK || avail_syrup<CHOCOLATE_SYRUP) {
            printf("Unavailable due to temporarily insufficient ingredients.\n");
            return; // returning to main menu
        }
        
    // for exiting the coffee order function
    } else if (choice == 0) {
        printf("Order canceled.\n");
        return; // returning to main menu
        
    // for any other input
    } else {
        printf("Invalid option entered. Please try again.\n");
        coffee_order(); // recursing to the beginning of the coffee order function
    }
    
    char confirm; // temporary choice variable
    printf("Confirm purchase of coffee %d? (Y/N): ",choice);
    scanf("%s", &confirm); // storing user's input
    
    if (confirm == 'Y'|| confirm == 'y'){
        payment(); // proceeding with payment
    } else {
        printf("Order canceled.\n"); // cancelling order & returning to main menu
    }
}

// FUNCTION FOR ADMIN MODE
void admin_mode(){
    while (1){
        // printing the menu of the admin mode
        printf("------------------------------\n");
        printf("|         ADMIN  MODE        |\n");
        printf("------------------------------\n");
        printf("| 1 - View Sales             |\n");
        printf("| 2 - Replenish Ingredients  |\n");
        printf("| 3 - Update Pricing         |\n");
        printf("| 0 - Exit Admin Mode        |\n");
        printf("------------------------------\n");

        int admin_choice; // temporary variable for choosing option
        printf("Please choose an option (0/1/2/3): ");
        scanf("%d",&admin_choice); // storing chosen option

        if (admin_choice == 1){
            // displaying the ingredients & total sale amount of the machine
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

            char update_amt; // temporary variable for choice
            printf("Would you like to reset the total sale amount to zero? (Y/N): ");
            scanf("%s",&update_amt); // storing input into temporary variable
            
            // if the user chooses to reset the total sale amount
            if (update_amt == 'Y' || update_amt == 'y'){
                total_amount = 0.0; // resetting the total amount
                printf("Total sale amount resetted. Please collect the money from the machine.\n");
                continue; // looping back to the beginning of the admin mode
            } else {
                continue; // looping back to the beginning of the admin mode
            }
            
        } else if (admin_choice == 2){
            // printing the old quantities
            printf("Old quantity of beans : %d\n",avail_beans);
            printf("Old quantity of water : %d\n",avail_water);
            printf("Old quantity of milk : %d\n",avail_milk);
            printf("Old quantity of chocolate syrup : %d\n",avail_syrup);
            
            // generating random quantities, while using % to set the limit equivalent to the ingredients needed for 20 cups
            avail_beans = rand() % 305 + THRESHOLD_BEANS; 
            avail_water = rand() % 1521 + THRESHOLD_WATER;
            avail_milk = rand() % 6081 + THRESHOLD_MILK;
            avail_syrup = rand()% 1141 + THRESHOLD_CHOCOLATE_SYRUP;
            
            // printing the updated quantities
            printf("New quantity of beans : %d\n",avail_beans);
            printf("New quantity of water : %d\n",avail_water);
            printf("New quantity of milk : %d\n",avail_milk);
            printf("New quantity of chocolate syrup : %d\n",avail_syrup);
            
        } else if (admin_choice == 3){
            // displaying the coffee menu
            printf("---------------------------\n");
            printf("|        COFFEE LIST      |\n");
            espresso();
            cappuccino();
            mocha();

            int choice4; // defining a temporary choice variable
            double new_price; // defining a temporary variable to update pricing
            
            printf("Which coffee price would you like to update? (1/2/3): "); 
            scanf("%d",&choice4); // input from user that indicates the coffee option

            // for espresso
            if (choice4 == 1){
                espresso(); // displaying details of the coffee
                printf("Please enter the updated price: "); 
                scanf("%lf",&new_price); // saving the updated price into a temp variable
                ESPRESSO_PRICE = new_price; // updating the current price
                printf("Price updated successfully!\n");
                espresso(); // displaying the updated coffee details
                
            // for cappuccino
            } else if (choice4 == 2){
                cappuccino(); // displaying details of the coffee
                printf("Please enter the updated price: ");
                scanf("%lf",&new_price); // saving the updated price into a temp variable
                CAPPUCCINO_PRICE = new_price; // updating the current price
                printf("Price updated successfully!\n");
                cappuccino(); // displaying the updated coffee details
                
            // for mocha
            } else if (choice4 == 3){
                mocha(); // displaying details of the coffee
                printf("Please enter the updated price: ");
                scanf("%lf",&new_price); // saving the updated price into a temp variable
                MOCHA_PRICE = new_price; // updating the current price
                printf("Price updated successfully!\n");
                mocha(); // displaying the updated coffee details
                
            // for any other input
            } else {
                printf("Invalid option entered. Please try again.\n");
                continue; // looping back to the beginning of the coffee menu
            }
            
        // for exiting the admin mode    
        } else if (admin_choice == 0){
            printf("Thank you for using the operator mode.\n");
            break; // exits the admin mode loop
            
        // for any other input
        } else {
            printf("Invalid option entered. Please try again. \n");
            continue; // loops back to the beginning of the admin mode
        }

    }
}

// FUNCTION FOR MAIN MENU
void main_menu() {
    while (1) {
        // displaying the main menu
        printf("---------------------------\n");
        printf("|      COFFEE  MACHINE    |\n");
        printf("---------------------------\n");
        printf("| 1. Order Coffee         |\n");
        printf("| 2. Admin Mode           |\n");
        printf("| 3. Exit                 |\n");
        printf("---------------------------\n");
        
        int user_choice; // temporary variable to choose option
        printf("Please choose an option (1/2/3): ");
        scanf("%d",&user_choice); // storing user's choice
        
        if (user_choice == 1){
            coffee_order(); // redirecting to the coffee order function 
            
        } else if (user_choice == 2) {
            int passcode; // temporary variable for checking admin passcode
            printf("Enter the admin password: ");
            scanf("%d", &passcode); // storing the user's input
            
            if (passcode == ADMIN_PASSWORD) {
                admin_mode(); // if the password matches, the user is redirected to the admin mode
            } else {
                printf("Incorrect password entered. Please try again.\n"); // upon password rejection
            }
            
        } else if (user_choice == 3) {
            printf("Thank you for using the coffee machine. Hope you have a pleasant day! :)\n");
            break; // exiting the coffee machine
            
        } else {
            printf("Invalid input.\n");
            continue; // looping back to the beginning of the main menu
        }
    }
}
// MAIN FUNCTION
int main() {
    int i; 
    main_menu(); // redirecting to the main menu function
    return 0;
}