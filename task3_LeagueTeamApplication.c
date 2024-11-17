// --- TASK 3: LEAGUE TEAM APPLICATION ---

// HEADERS
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// CONSTANTS
#define NUM_TEAMS 6 // number of participating teams
#define SQUAD_SIZE 11 // number of participating players
#define NAME_LENGTH 25 // length of player's name
#define TEAM_LENGTH 20 // length of team's name
#define ROLE_LENGTH 30 // length of player's position

// FUNCTION PROTOTYPES

// required udfs
void display_menu(); // function that continually displays the text menu
void enroll_club(); // function that allows user to enroll a team
void add_player(); // function that allows user to add player
void search_update(); // function that allows user to update player's details
void display_club_statistics(); // function that displays the statistics of all the clubs

// utility udfs
void age_calculation(int ageteam[],int ind_age[][SQUAD_SIZE]); // function that calculates age of player's & average age
void string_reader(char str[],int max_len); // function that reads strings with whitespaces, without newlines

// STRUCTURES

// structure for date of birth of player
typedef struct {
    int dd; // day of birth
    int mm; // month of birth
    int yyyy; // year of birth
} age_structure;

// structure for player attributes
typedef struct {
    char name[NAME_LENGTH]; // name of player
    int kit_num; // kit number of player
    char club[TEAM_LENGTH]; // club name of player
    age_structure dob; // age structure, referenced by 'dob'
    char position[ROLE_LENGTH]; // position of player
} player_t;

// structure for team attributes
typedef struct {
    char name[TEAM_LENGTH]; // name of team
    player_t team_players[SQUAD_SIZE]; // player structure, referenced by 'team_players'
    int ActiveSize; // number of active players of the team
} team_t;

// GLOBAL CONTROL VARIABLES
team_t teams[NUM_TEAMS]; // team structure, represented by an array 'teams'
int enrolledteams = 0; // number of enrolled teams


// FUNCTION DEFINITIONS

// function to display the main menu
void display_menu() {
    while (1) {
        printf("---------------------------------\n");
        printf("|      UEFA CHAMPIONS LEAGUE    |\n");
        printf("---------------------------------\n");
        printf("| 1. Enroll Club                |\n");
        printf("| 2. Add Player                 |\n");
        printf("| 3. Update Player Details      |\n");
        printf("| 4. Show Club Statistics       |\n");
        printf("| 5. Exit League Menu           |\n");
        printf("---------------------------------\n");
       
        int user_choice; // temporary variable to choose option
        printf("Please choose an option (1/2/3/4/5): ");
        scanf("%d",&user_choice); // storing user's choice
        getchar(); // clearing newline
       
        if (user_choice == 1){
            enroll_club(); // redirecting to the club enroll function
           
        } else if (user_choice == 2) {
            add_player(); // redirecting to the add player function
           
        } else if (user_choice == 3) {
            search_update(); // redirecting to update function
           
        } else if (user_choice == 4) {
            display_club_statistics(); // redirecting to display stats function
           
        } else if (user_choice == 5) {
            printf("Thank you for using the UEFA application.\n");
            break; // terminating program
        } else {
            printf("Invalid input. Terminating program...\n");
            break; // terminating program for any other input
        }
    }
}

// utility function to read strings with spaces
void string_reader(char str[], int max_len) { // inputs are the string and the length of the string
    fgets(str,max_len,stdin); // read string w spaces
    str[strcspn(str,"\n")] = '\0'; // to replace newline character
}

// enrolling a club
void enroll_club() {
    if (enrolledteams<NUM_TEAMS) { // if the number of enrolled teams is less than the max. number of teams
        char club_name[TEAM_LENGTH]; // temporary variable that stores the club name from the user
        int found = 0; // temporary variable that checks whether the club is enrolled
        printf("Please enter the club name: "); // asking user for team name
        string_reader(club_name,TEAM_LENGTH); // reading string

        for (int i = 0; i<enrolledteams; i++) {
            if (strcasecmp(teams[i].name,club_name) == 0) { // using strcasecmp() to check whether club is enrolled
                found++; // variable incremented
            }
        }
        if (found!=0) {
            printf("Error: Club already exists in database.\n"); // handling error
            return;
        } else { // if club is not enrolled
            strcpy(teams[enrolledteams].name,club_name); // using strcpy() to store the user's input in list of clubs
            printf("Club successfully enrolled.\n");
            teams[enrolledteams].ActiveSize = 0; // setting the active players to zero
            enrolledteams++; // post-incrementing the number of enrolled teams
        }
    } else { // handling error
        printf("Error: Maximum number of clubs reached.\n");
        return;
    }
}

// adding a player to team
void add_player() {
    if (enrolledteams == 0) { // handling error
        printf("Error: No clubs enrolled. Please enroll a club and try again.\n");
        return;
    }
    printf("---  CLUB LIST  ---\n");
    for (int i = 0; i<enrolledteams; i++) {
        printf("%d. %s\n",i+1,teams[i].name); // printing list of clubs
    }
    int choice;
    printf("Please enter your selection: ");
    scanf("%d",&choice); // storing user's selection
    getchar(); // clearing newline
   
    // statements to check if user has selected an existing club
    int j = 0;
    for (int i = 0; i<enrolledteams; i++) {
        if ((i+1) == choice) {
            j++;
        }
    }
    if (j == 0) { // if club not found, handling error
        printf("Error: Invalid input entered. Please try again.\n");
        return;
       
    } else if (teams[choice-1].ActiveSize==SQUAD_SIZE) { // handling error if max players present
        printf("Error: Maximum number of players already enrolled.\n");
        return;
    }
   
    int player_index = teams[choice-1].ActiveSize; // initialising a variable for index of player
    char play_name[NAME_LENGTH]; // initialising an array for storing player name
    int kit_no; // variable for storing the kit number
    int found = 0; // variable for checking duplicates
   
    // loop will run till false is returned
    while (true) {
        int found = 0;
        printf("Enter the player's name: ");
        string_reader(play_name,NAME_LENGTH); // storing user's input
        do {
            printf("Enter the player's kit number (1-99): ");
            scanf("%d", &kit_no); // storing user's input
            getchar(); // clearing newline
            if (kit_no < 1 || kit_no > 99) {
                printf("Error: Kit number must be between 1 and 99.\n");
            }
        } while (kit_no < 1 || kit_no > 99);
       
        for (int i = 0;i<enrolledteams;i++){ // outer loop that will run for the number of teams
            for (int j = 0; j<player_index; j++){ // inner loop that will run for number of players
                // checking if player name & kit number both are found
                if ((strcasecmp(teams[i].team_players[j].name,play_name) == 0) || (kit_no == teams[i].team_players[j].kit_num)){
                    printf("Error: Player already in system.\n");
                    printf("Player Name: %s\n",teams[i].team_players[j].name);
                    printf("Kit Number: %d\n",teams[i].team_players[j].kit_num);
                    printf("Please enter new details.\n"); //prompting user to enter details again
                    found = 1; // found variable incremented
                }
            }
        }
       
        if (found == 0) { // if found hasn't been incremented
             // storing user input in struct
            strcpy(teams[choice-1].team_players[player_index].name,play_name);
            teams[choice-1].team_players[player_index].kit_num = kit_no;
            break; // returning false to break out of loop
        }
       
    }
   
    // storing player's dob in age struct
    printf("Enter the player's date of birth (dd,mm,yyyy): ");
    scanf("%d %d %d", &teams[choice-1].team_players[player_index].dob.dd,&teams[choice-1].team_players[player_index].dob.mm,&teams[choice-1].team_players[player_index].dob.yyyy);
    getchar(); // clearing newline
   
    // storing player's position in struct
    printf("Enter the position of the player: ");
    scanf("%s",&teams[choice-1].team_players[player_index].position);
    getchar(); // clearing newline
   
    strcpy(teams[choice-1].team_players[player_index].club,teams[choice-1].name); // setting the user's club name
    teams[choice-1].ActiveSize++; // incrementing active players
    printf("Player successfully added to %s.\n",teams[choice-1].name);
}

void search_update() {

    if (enrolledteams == 0) { // handling error
        printf("Error: No clubs enrolled. Please enroll a club and try again.\n");
        return;
    }

    int search_choice; // variable to store user's choice
    printf("Search Options:\n");
    printf("1. Player Name\n");
    printf("2. Kit Number\n");
    printf("Please enter your choice (1/2): ");
    scanf("%d", &search_choice); // storing user's choice
    getchar(); // clearing newline

    if (search_choice == 1) { // if user chooses to search by name
        char playername[NAME_LENGTH]; // temporary variable to store player's name
        printf("Please enter the player's full name: ");
        string_reader(playername,NAME_LENGTH); // storing user input
        int foundplayer = 0; // temporary variable to check if player is found

        for (int i = 0; i<enrolledteams; i++) {
            for (int j = 0; j<teams[i].ActiveSize; j++) {
                if (strcasecmp(teams[i].team_players[j].name,playername) == 0) {
                    foundplayer++; // incrementing the temp variable
                    printf("Player found in %s Club.\n",teams[i].team_players[j].club);
                    printf("1. Player name: %s\n",teams[i].team_players[j].name);
                    printf("2. Kit number: %d\n",teams[i].team_players[j].kit_num);
                    printf("3. Date of birth: %d/%d/%d\n",teams[i].team_players[j].dob.dd,teams[i].team_players[j].dob.mm,teams[i].team_players[j].dob.yyyy);
                    printf("4. Position: %s\n",teams[i].team_players[j].position);

                    while (true) { // will run till 0 is entered
                        int updatesearch; // user's choice for updating
                        printf("Which details would you like to update? (1/2/3/4) or 0 to cancel: ");
                        scanf("%d",&updatesearch); // storing user input
                        getchar(); // clearing newline

                        if (updatesearch == 1) { // for updating player's name
                            while (true) {
                                char name_attr[NAME_LENGTH]; // temporary variable to store name
                                int pla_index = teams[i].ActiveSize; // index for easy traversal
                                printf("Please enter the player's name: ");
                                string_reader(name_attr,NAME_LENGTH); // storing user input
                                int foundperson = 0; // temp variable to check if player already enrolled                        
                                for (int k = 0;k<enrolledteams;k++){ // outer loop that will run for the number of teams
                                    for (int l = 0; l<pla_index; l++){ // inner loop that will run for number of players
                                        // checking if player name & kit number both are found
                                        if (strcasecmp(teams[k].team_players[l].name,name_attr) == 0){
                                            printf("Error: Player already in system.\n"); // error
                                            printf("Player Name: %s\n",teams[k].team_players[l].name);
                                            printf("Kit Number: %d\n",teams[k].team_players[l].kit_num);
                                            printf("Please enter new details.\n"); //prompting user to enter details again
                                            foundperson = 1; // found variable incremented
                                        }
                                    }
                                }
                                if (foundperson == 0) { // if found hasn't been incremented
                                    // storing user input in struct
                                    strcpy(teams[i].team_players[j].name,name_attr); // using strcpy()
                                    break; // returning false to break out of loop
                                }
                            }
                            printf("Player name updated successfully.\n");

                        } else if (updatesearch == 2) { // if user chooses to update kit number
                            while (true) {
                                int kit_attr; // temp variable to store user input
                                int pla_index = teams[i].ActiveSize; // index for easy access

                                // do while loop to ensure that user enters a kit number in specified range
                                do {
                                    printf("Enter the player's kit number (1-99): ");
                                    scanf("%d", &kit_attr); // storing user's input
                                    getchar(); // clearing newline
                                    if (kit_attr < 1 || kit_attr > 99) {
                                        printf("Error: Kit number must be between 1 and 99.\n");
                                    }
                                } while (kit_attr < 1 || kit_attr > 99);

                                int foundperson = 0; // temp variable to check if player is already enrolled                             
                                for (int k = 0;k<enrolledteams;k++){ // outer loop that will run for the number of teams
                                    for (int l = 0; l<pla_index; l++){ // inner loop that will run for number of players
                                        // checking if player name & kit number both are found
                                        if (teams[k].team_players[l].kit_num == kit_attr){
                                            printf("Error: Player already in system.\n"); // error
                                            printf("Player Name: %s\n",teams[k].team_players[l].name);
                                            printf("Kit Number: %d\n",teams[k].team_players[l].kit_num);
                                            printf("Please enter new details.\n"); //prompting user to enter details again
                                            foundperson = 1; // found variable incremented
                                        }
                                    }
                                }
                                if (foundperson == 0) { // if found hasn't been incremented
                                    // storing user input in struct
                                    teams[i].team_players[j].kit_num = kit_attr;
                                    break; // returning false to break out of loop
                                }
                            }
                            printf("Kit number updated successfully.\n");

                        } else if (updatesearch == 3) { // if user updates dob
                            printf("Enter the new date of birth (dd/mm/yyyy): ");
                            // storing user input
                            scanf("%d %d %d",&teams[i].team_players[j].dob.dd,&teams[i].team_players[j].dob.mm,&teams[i].team_players[j].dob.yyyy);
                            getchar(); // clearing newline
                            printf("Date of birth updated successfully.\n");
                           
                        } else if (updatesearch == 4) { // if user updates position
                            printf("Enter the new position of the player: ");
                            // storing user input
                            scanf("%s",&teams[i].team_players[j].position);
                            getchar(); // clearing newline
                            printf("Position updated successfully.\n");

                        } else if (updatesearch == 0) { // if user cancels
                            printf("Update canceled.\n");
                            break; // breaking out of loop to menu

                        } else { // if user inputs anything else
                            printf("Error: Invalid input. Please enter a valid option.\n"); // handling error
                        }
                    }
                }
            }
        }

        if (foundplayer == 0) { // handling error
            printf("Error: Player not found.\n");
            return;
        }

    } if (search_choice == 2) { // if user chooses to update by kit number
        int kityes; // temp variable to store user input
        printf("Please enter the player's kit number: ");
        scanf("%d",&kityes); // storing user input
        getchar(); // clearing newline
        int foundplayer = 0; // temp variable to check if player in system

        for (int i = 0; i<enrolledteams; i++) {
            for (int j = 0; j<teams[i].ActiveSize; j++) {
                if (teams[i].team_players[j].kit_num == kityes) {
                    foundplayer++; // incrementing temp variable if player found
                    printf("Player found in %s Club.\n",teams[i].team_players[j].club);
                    printf("1. Player name: %s\n",teams[i].team_players[j].name);
                    printf("2. Kit number: %d\n",teams[i].team_players[j].kit_num);
                    printf("3. Date of birth: %d/%d/%d\n",teams[i].team_players[j].dob.dd,teams[i].team_players[j].dob.mm,teams[i].team_players[j].dob.yyyy);
                    printf("4. Position: %s\n",teams[i].team_players[j].position);
                    while (true) {
                        int updatesearch; // temp variable for user input
                        printf("Which details would you like to update? (1/2/3/4) or 0 to cancel: ");
                        scanf("%d",&updatesearch); // storing user input
                        getchar(); // clearing newline
                        if (updatesearch == 1) { // if user wants to update player name
                            while (true) {
                                char name_attr[NAME_LENGTH]; // temp variable for user input
                                int pla_index = teams[i].ActiveSize; // index for easy access
                                printf("Please enter the player's name: ");
                                string_reader(name_attr,NAME_LENGTH); // storing user input
                                int foundperson = 0; // temp variable to check if name already in system                        
                                for (int k = 0;k<enrolledteams;k++){ // outer loop that will run for the number of teams
                                    for (int l = 0; l<pla_index; l++){ // inner loop that will run for number of players
                                        // checking if player name & kit number both are found
                                        if (strcasecmp(teams[k].team_players[l].name,name_attr) == 0){
                                            printf("Error: Player already in system.\n"); // error
                                            printf("Player Name: %s\n",teams[k].team_players[l].name);
                                            printf("Kit Number: %d\n",teams[k].team_players[l].kit_num);
                                            printf("Please enter new details.\n"); //prompting user to enter details again
                                            foundperson = 1; // found variable incremented
                                        }
                                    }
                                }
                                if (foundperson == 0) { // if found hasn't been incremented
                                    // storing user input in struct
                                    strcpy(teams[i].team_players[j].name,name_attr); // using strcpy()
                                    break; // returning false to break out of loop
                                }
                            }
                            printf("Player name updated successfully.\n");

                        } else if (updatesearch == 2) { // if user chooses to update kit number
                            while (true) {
                                int kit_attr; // temp var for user input
                                int pla_index = teams[i].ActiveSize; // index for easy access
                                // do while loop to ensure that user enters a value between 1 and 99
                                do {
                                    printf("Enter the player's kit number (1-99): ");
                                    scanf("%d", &kit_attr); // storing user's input
                                    getchar(); // clearing newline
                                    if (kit_attr < 1 || kit_attr > 99) {
                                        printf("Error: Kit number must be between 1 and 99.\n");
                                    }
                                } while (kit_attr < 1 || kit_attr > 99);
                                int foundperson = 0; // temp var for checking if kit numebr alr in system                 
                                for (int k = 0;k<enrolledteams;k++){ // outer loop that will run for the number of teams
                                    for (int l = 0; l<pla_index; l++){ // inner loop that will run for number of players
                                        // checking if player name & kit number both are found
                                        if (teams[k].team_players[l].kit_num == kit_attr){
                                            printf("Error: Player already in system.\n");// error
                                            printf("Player Name: %s\n",teams[k].team_players[l].name);
                                            printf("Kit Number: %d\n",teams[k].team_players[l].kit_num);
                                            printf("Please enter new details.\n"); //prompting user to enter details again
                                            foundperson = 1; // found variable incremented
                                        }
                                    }
                                }
                                if (foundperson == 0) { // if found hasn't been incremented
                                    // storing user input in struct
                                    teams[i].team_players[j].kit_num = kit_attr; 
                                    break; // returning false to break out of loop
                                }
                            }
                            printf("Kit number updated successfully.\n");

                        } else if (updatesearch == 3) { // if user wants to update dob
                            printf("Enter the new date of birth (dd/mm/yyyy): ");
                            // storing user input
                            scanf("%d %d %d",&teams[i].team_players[j].dob.dd,&teams[i].team_players[j].dob.mm,&teams[i].team_players[j].dob.yyyy);
                            getchar(); // clearing newline
                            printf("Date of birth updated successfully.\n");
                           
                        } else if (updatesearch == 4) { // if user wants to update position
                            printf("Enter the new position of the player: ");
                            scanf("%s",&teams[i].team_players[j].position); // storing user input
                            getchar(); // clearing newline
                            printf("Position updated successfully.\n");

                        } else if (updatesearch == 0) { // if user cancels
                            printf("Update canceled.\n");
                            break; // breaks back to menu

                        } else { // if user enters invalid input
                            printf("Error: Invalid input. Please enter a valid option.\n"); // handling error
                        }
                    }
                }
            }
        }

        if (foundplayer == 0) { // handling error
            printf("Error: Player not found.\n");
            return;
        }
    }
}

// function to calculate individual age of player & to calculate average age of team
void age_calculation(int ageteam[], int ind_age[enrolledteams][SQUAD_SIZE]) {
    int year = 2024; // current year
    int month = 11; // current month
    int day = 16; // current date
    for (int i = 0; i<enrolledteams; i++) {
        int total_age = 0; // variable for calculating sum of ages of all players
        for (int j = 0; j<teams[i].ActiveSize; j++) { // inner loop goes for the number of active players of each team
            int age = (year-teams[i].team_players[j].dob.yyyy); // variable for calculating age of player
            // which is decremented case-wise
            // if the current month is less than the player's birth month
            // if the current month and birth month is same but the current day is less than the player's birth day
            if (month<teams[i].team_players[j].dob.mm || ((month == teams[i].team_players[j].dob.mm) && (day<teams[i].team_players[j].dob.dd))){
                age--; // decreased by 1
            }
            ind_age[i][j] = age; // individual age of player set
            total_age+=age; // individual age added to variable for total age
        }
        if (teams[i].ActiveSize>0){ // as long as there are players in team
            ageteam[i] = total_age/teams[i].ActiveSize; // calculating average
        } else { // if no players in team
            ageteam[i] = 0; // average age is set to zero
        }
    }
}

// function for displaying club's statistics
void display_club_statistics() {
    if (enrolledteams == 0) { // handling error
        printf("Error: No clubs enrolled. Please enroll a club and try again.\n");
        return;

    } else {
        int ageteam[enrolledteams]; // initialising variable for team's average age
        int ind_age[enrolledteams][SQUAD_SIZE]; // initialising variable for player's age
        age_calculation(ageteam,ind_age); // function to calculate individual & average ages
        for (int i = 0; i<enrolledteams;i++){ // outer loop traverses through clubs
            // printing club's details
            printf("Club %d: %s\n",i+1,teams[i].name); 
            printf("Number of players: %d\n",teams[i].ActiveSize);
            printf("Average age of players: %d\n",ageteam[i]); 
            if (teams[i].ActiveSize == 0) { // if there are no players in the club the loop is forced to next iteration
                break;
            } else {
                printf("Player details: \n");
                printf("-------------------------------\n");
            }
            for (int j = 0; j<teams[i].ActiveSize; j++) { // inner loop traverses through team players & prints their details
                printf("1. Player name: %s\n",teams[i].team_players[j].name);
                printf("2. Kit number: %d\n",teams[i].team_players[j].kit_num);
                printf("3. Date of birth: %d/%d/%d\n",teams[i].team_players[j].dob.dd,teams[i].team_players[j].dob.mm,teams[i].team_players[j].dob.yyyy);
                printf("4. Position: %s\n",teams[i].team_players[j].position);
                printf("5. Age: %d\n",ind_age[i][j]); 
                printf("-------------------------------\n");
            }
        }
    }
}

// main function
int main() {
    int i;
    display_menu(); // displays the main menu
    return 0;
}