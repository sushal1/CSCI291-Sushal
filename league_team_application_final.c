#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// CONSTANTS
#define NUM_TEAMS 6
#define SQUAD_SIZE 11
#define NAME_LENGTH 25
#define TEAM_LENGTH 20
#define ROLE_LENGTH 30

// FUNCTION PROTOTYPES
void display_menu();
void enroll_club();
void add_player();
void search_update();
void display_club_statistics();
void age_calculation(int ageteam[],int ind_age[][SQUAD_SIZE]);
void string_reader(char str[],int max_len);

// STRUCTURES
typedef struct {
    int dd;
    int mm;
    int yyyy;
} age_structure;

typedef struct {
    char name[NAME_LENGTH];
    int kit_num;
    char club[TEAM_LENGTH];
    age_structure dob;
    char position[ROLE_LENGTH];
} player_t;

typedef struct {
    char name[TEAM_LENGTH];
    player_t team_players[SQUAD_SIZE];
    int ActiveSize;
} team_t;

team_t teams[NUM_TEAMS];
int enrolledteams = 0;


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
        getchar();
       
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
void string_reader(char str[], int max_len) {
    fgets(str,max_len,stdin); // read string w spaces
    str[strcspn(str,"\n")] = '\0'; // to replace newline character
}


// enrolling a club
void enroll_club() {
    if (enrolledteams<=NUM_TEAMS) {
        char club_name[TEAM_LENGTH];
        int found = 0;
        printf("Please enter the club name: "); // asking user for team name
        string_reader(club_name,TEAM_LENGTH); // utility function
        for (int i = 0; i<enrolledteams; i++) {
            if (strcasecmp(teams[i].name,club_name) == 0) {
                found++;
            }
        }
        if (found!=0) {
            printf("Club already exists in database.\n"); // handling error
            return;
        } else {
            strcpy(teams[enrolledteams].name,club_name);
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
                    printf("Player already in system.\n");
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

    int search_choice;
    printf("Search Options:\n");
    printf("1. Player Name\n");
    printf("2. Kit Number\n");
    printf("Please enter your choice (1/2): ");
    scanf("%d", &search_choice);
    getchar(); // clearing newline

    if (search_choice == 1) {
        char playername[NAME_LENGTH];
        printf("Please enter the player's full name: ");
        string_reader(playername,NAME_LENGTH);
        int foundplayer = 0;

        for (int i = 0; i<enrolledteams; i++) {
            for (int j = 0; j<teams[i].ActiveSize; j++) {
                if (strcasecmp(teams[i].team_players[j].name,playername) == 0) {
                    foundplayer++;
                    printf("Player found in %s Club.\n",teams[i].team_players[j].club);
                    printf("1. Player name: %s\n",teams[i].team_players[j].name);
                    printf("2. Kit number: %d\n",teams[i].team_players[j].kit_num);
                    printf("3. Date of birth: %d/%d/%d\n",teams[i].team_players[j].dob.dd,teams[i].team_players[j].dob.mm,teams[i].team_players[j].dob.yyyy);
                    printf("4. Position: %s\n",teams[i].team_players[j].position);
                    while (true) {
                        int updatesearch;
                        printf("Which details would you like to update? (1/2/3/4) or 0 to cancel: ");
                        scanf("%d",&updatesearch);
                        getchar();
                        if (updatesearch == 1){
                            while (true) {
                                char name_attr[NAME_LENGTH];
                                int pla_index = teams[i].ActiveSize;
                                printf("Please enter the player's name: ");
                                string_reader(name_attr,NAME_LENGTH);
                                int foundperson = 0;                              
                                for (int k = 0;k<enrolledteams;k++){ // outer loop that will run for the number of teams
                                    for (int l = 0; l<pla_index; l++){ // inner loop that will run for number of players
                                        // checking if player name & kit number both are found
                                        if (strcasecmp(teams[k].team_players[l].name,name_attr) == 0){
                                            printf("Player already in system.\n");
                                            printf("Player Name: %s\n",teams[k].team_players[l].name);
                                            printf("Kit Number: %d\n",teams[k].team_players[l].kit_num);
                                            printf("Please enter new details.\n"); //prompting user to enter details again
                                            foundperson = 1; // found variable incremented
                                        }
                                    }
                                }
                                if (foundperson == 0) { // if found hasn't been incremented
                                    // storing user input in struct
                                    strcpy(teams[i].team_players[j].name,name_attr);
                                    break; // returning false to break out of loop
                                }
                            }
                            printf("Player name updated successfully.\n");

                        } else if (updatesearch == 2) {
                            while (true) {
                                int kit_attr;
                                int pla_index = teams[i].ActiveSize;
                                do {
                                    printf("Enter the player's kit number (1-99): ");
                                    scanf("%d", &kit_attr); // storing user's input
                                    getchar(); // clearing newline
                                    if (kit_attr < 1 || kit_attr > 99) {
                                        printf("Error: Kit number must be between 1 and 99.\n");
                                    }
                                } while (kit_attr < 1 || kit_attr > 99);
                                int foundperson = 0;                              
                                for (int k = 0;k<enrolledteams;k++){ // outer loop that will run for the number of teams
                                    for (int l = 0; l<pla_index; l++){ // inner loop that will run for number of players
                                        // checking if player name & kit number both are found
                                        if (teams[k].team_players[l].kit_num == kit_attr){
                                            printf("Player already in system.\n");
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

                        } else if (updatesearch == 3) {
                            printf("Enter the new date of birth (dd/mm/yyyy): ");
                            scanf("%d %d %d",&teams[i].team_players[j].dob.dd,&teams[i].team_players[j].dob.mm,&teams[i].team_players[j].dob.yyyy);
                            getchar(); // clearing newline
                            printf("Date of birth updated successfully.\n");
                           
                        } else if (updatesearch == 4) {
                            printf("Enter the new position of the player: ");
                            scanf("%s",&teams[i].team_players[j].position);
                            getchar(); // clearing newline
                            printf("Position updated successfully.\n");

                        } else if (updatesearch == 0) {
                            printf("Update canceled.\n");
                            break;

                        } else {
                            printf("Please enter a valid option.\n");
                        }
                    }
                }
            }
        }

        if (foundplayer == 0) { // handling error
            printf("Player not found.\n");
            return;
        }
    } if (search_choice == 2) {
        int kityes;
        printf("Please enter the player's kit number: ");
        scanf("%d",&kityes);
        getchar();
        int foundplayer = 0;

        for (int i = 0; i<enrolledteams; i++) {
            for (int j = 0; j<teams[i].ActiveSize; j++) {
                if (teams[i].team_players[j].kit_num == kityes) {
                    foundplayer++;
                    printf("Player found in %s Club.\n",teams[i].team_players[j].club);
                    printf("1. Player name: %s\n",teams[i].team_players[j].name);
                    printf("2. Kit number: %d\n",teams[i].team_players[j].kit_num);
                    printf("3. Date of birth: %d/%d/%d\n",teams[i].team_players[j].dob.dd,teams[i].team_players[j].dob.mm,teams[i].team_players[j].dob.yyyy);
                    printf("4. Position: %s\n",teams[i].team_players[j].position);
                    while (true) {
                        int updatesearch;
                        printf("Which details would you like to update? (1/2/3/4) or 0 to cancel: ");
                        scanf("%d",&updatesearch);
                        getchar();
                        if (updatesearch == 1){
                            while (true) {
                                char name_attr[NAME_LENGTH];
                                int pla_index = teams[i].ActiveSize;
                                printf("Please enter the player's name: ");
                                string_reader(name_attr,NAME_LENGTH);
                                int foundperson = 0;                              
                                for (int k = 0;k<enrolledteams;k++){ // outer loop that will run for the number of teams
                                    for (int l = 0; l<pla_index; l++){ // inner loop that will run for number of players
                                        // checking if player name & kit number both are found
                                        if (strcasecmp(teams[k].team_players[l].name,name_attr) == 0){
                                            printf("Player already in system.\n");
                                            printf("Player Name: %s\n",teams[k].team_players[l].name);
                                            printf("Kit Number: %d\n",teams[k].team_players[l].kit_num);
                                            printf("Please enter new details.\n"); //prompting user to enter details again
                                            foundperson = 1; // found variable incremented
                                        }
                                    }
                                }
                                if (foundperson == 0) { // if found hasn't been incremented
                                    // storing user input in struct
                                    strcpy(teams[i].team_players[j].name,name_attr);
                                    break; // returning false to break out of loop
                                }
                            }
                            printf("Player name updated successfully.\n");

                        } else if (updatesearch == 2) {
                            while (true) {
                                int kit_attr;
                                int pla_index = teams[i].ActiveSize;
                                do {
                                    printf("Enter the player's kit number (1-99): ");
                                    scanf("%d", &kit_attr); // storing user's input
                                    getchar(); // clearing newline
                                    if (kit_attr < 1 || kit_attr > 99) {
                                        printf("Error: Kit number must be between 1 and 99.\n");
                                    }
                                } while (kit_attr < 1 || kit_attr > 99);
                                int foundperson = 0;                              
                                for (int k = 0;k<enrolledteams;k++){ // outer loop that will run for the number of teams
                                    for (int l = 0; l<pla_index; l++){ // inner loop that will run for number of players
                                        // checking if player name & kit number both are found
                                        if (teams[k].team_players[l].kit_num == kit_attr){
                                            printf("Player already in system.\n");
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

                        } else if (updatesearch == 3) {
                            printf("Enter the new date of birth (dd/mm/yyyy): ");
                            scanf("%d %d %d",&teams[i].team_players[j].dob.dd,&teams[i].team_players[j].dob.mm,&teams[i].team_players[j].dob.yyyy);
                            getchar(); // clearing newline
                            printf("Date of birth updated successfully.\n");
                           
                        } else if (updatesearch == 4) {
                            printf("Enter the new position of the player: ");
                            scanf("%s",&teams[i].team_players[j].position);
                            getchar(); // clearing newline
                            printf("Position updated successfully.\n");

                        } else if (updatesearch == 0) {
                            printf("Update canceled.\n");
                            break;

                        } else {
                            printf("Please enter a valid option.\n");
                        }
                    }
                }
            }
        }

        if (foundplayer == 0) { // handling error
            printf("Player not found.\n");
            return;
        }
    }
}

void age_calculation(int ageteam[], int ind_age[enrolledteams][SQUAD_SIZE]) {
    int year = 2024;
    int month = 11;
    int day = 16;
    for (int i = 0; i<enrolledteams; i++) {
        int total_age = 0;
        for (int j = 0; j<teams[i].ActiveSize; j++) {
            int age = (year-teams[i].team_players[j].dob.yyyy);
            if (month<teams[i].team_players[j].dob.mm || ((month == teams[i].team_players[j].dob.mm) && (day<teams[i].team_players[j].dob.dd))){
                age--;
            }
            ind_age[i][j] = age;
            total_age+=age;
        }
        if (teams[i].ActiveSize>0){
            ageteam[i] = total_age/teams[i].ActiveSize;
        } else {
            ageteam[i] = 0;
        }
    }
}

void display_club_statistics() {
    if (enrolledteams == 0) {
        printf("Error: No clubs enrolled. Please enroll a club and try again.\n");
        return;
    } else {
        int ageteam[enrolledteams];
        int ind_age[enrolledteams][SQUAD_SIZE];
        age_calculation(ageteam,ind_age);
        for (int i = 0; i<enrolledteams;i++){
            printf("Club %d: %s\n",i+1,teams[i].name);
            printf("Number of players: %d\n",teams[i].ActiveSize);
            printf("Average age of players: %d\n",ageteam[i]);
            if (teams[i].ActiveSize == 0) {
                break;
            } else {
                printf("Player details: \n");
                printf("-------------------------------\n");
            }
            for (int j = 0; j<teams[i].ActiveSize; j++) {
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

int main() {
    int i;
    display_menu();
    return 0;
}