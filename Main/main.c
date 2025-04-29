#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100

int isTimeOverlapping(const char *filename, const char *newTime);
void saveSchedule();
void viewAllSchedules();
void viewSpecificSchedule();
void asciiArt();

int main() {
    int choice;
    
    asciiArt();
    
   //32 blank spaces

    do
    {
    
    printf("\n\n                                ================================================================================================\n");
    printf("                                |                           COMPUTER LABORATORY SCHEDULE MENU                                  |\n");
    printf("                                ================================================================================================\n");
    printf("                                | 1. New Schedule                                 3. Display Day Schedule                      |\n");
    printf("                                | 2. Display All Schedules                        4. Exit                                      |\n");
    printf("                                ================================================================================================\n");
    printf("\n                                Enter your choice: ");
    scanf("%d", &choice);
        
        if (choice == 1) {
            saveSchedule();
        } else if (choice == 2) {
            viewAllSchedules();
        } else if (choice == 3) {
            viewSpecificSchedule();
        } else if (choice == 4) {
            printf("Exiting...\n");
            break;
        } else {
            printf("Invalid choice! Please try again.\n");
        }
        
    } while (choice != 4 || choice == 0);


    return 0;
}



//FUNTIONS--------------------------------------------------------------

// Function to check if a given time overlaps with existing schedules
int isTimeOverlapping(const char *filename, const char *newTime) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return 0; // No existing schedules, no overlap
    }

    char line[MAX_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "Time Schedule:")) {
            if (strstr(line, newTime)) {
                fclose(file);
                return 1; // Overlapping schedule found
            }
        }
    }

    fclose(file);
    return 0; // No overlap found
}

// Function to save a new schedule
void saveSchedule() {
    char day[20], schedule1[MAX_LENGTH];
    char sub[20], schedule2[MAX_LENGTH];
    char section[20], schedule3[MAX_LENGTH];

    printf("                                Enter the day (Monday, Tuesday, Thursday, Friday): ");
    scanf("%s", day);
    getchar(); // Consume newline character

    char filename[30];
    strcpy(filename, day);
    strcat(filename, ".txt");

    printf("                                Enter the time schedule: ");
    fgets(schedule1, MAX_LENGTH, stdin);
    schedule1[strcspn(schedule1, "\n")] = 0; // Remove newline character

    if (isTimeOverlapping(filename, schedule1)) {
        printf("                            Time schedule overlaps with an existing schedule.\n");
        return;
    }

    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("                            Error opening file!\n");
        return;
    }
    

    
    // SCHEDULING
    fprintf(file, "\nTime Schedule: %s\n", schedule1);

    printf("                                Enter the Subject: ");
    fgets(schedule2, MAX_LENGTH, stdin);
    fprintf(file, "Subject: %s", schedule2);

    printf("                                Enter the Section: ");
    fgets(schedule3, MAX_LENGTH, stdin);
    fprintf(file, "Section: %s", schedule3);

    fclose(file);

    printf("                                Schedule saved successfully for %s!\n", day);
}

//Viewing all Schedules
void viewAllSchedules() {
    char *days[] = {"                       Monday", "Tuesday", "Thursday", "Friday"};
    char filename[30], line[MAX_LENGTH];

    printf("\n                              All Schedules:\n");
    for (int i = 0; i < 4; i++) {
        strcpy(filename, days[i]);
        strcat(filename, ".txt");

        FILE *file = fopen(filename, "r");
        if (file != NULL) {
            printf("\n\n%s:\n", days[i]);
            while (fgets(line, MAX_LENGTH, file)) {
                printf("%s", line);
            }
            fclose(file);
        } else {
            printf("\n                      %s: No schedules found!\n", days[i]);
        }
    }
}

//Viewing specific schedule
void viewSpecificSchedule() {
    char day[20], filename[30], line[MAX_LENGTH];
    printf("                               Enter the day to view schedule (Monday, Tuesday, Thursday, Friday): ");
    scanf("%s", day);

    strcpy(filename, day);
    strcat(filename, ".txt");

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("                           No schedules found for %s!\n", day);
        return;
    }

    printf("\n                             Schedule for %s:\n", day);
    while (fgets(line, MAX_LENGTH, file)) {
        printf("%s", line);
    }
    fclose(file);
}


void asciiArt(){

    printf("                                +==============================================================================================+ \n"); 
    printf("                                | ######   #######  ##     ## ##          ###    ########                                      |\n");
    printf("                                |##    ## ##     ## ###   ### ##         ## ##   ##     ##                                     |\n");
    printf("                               	|##       ##     ## #### #### ##        ##   ##  ##     ##                                     |\n");
    printf("                                |##       ##     ## ## ### ## ##       ##     ## ########                                      |\n");
    printf(" #@@@@@@@@ #@@@@@@@@ @@@= @@@#  |##       ##     ## ##     ## ##       ######### ##     ##                                     |\n");
    printf(" #@@= @@@@ #@@@#@@@@ @@@= @@@#  |##    ## ##     ## ##     ## ##       ##     ## ##     ##                                     |\n");
    printf(" #@@@#@@@# #@@* *@@@ @@@= @@@#  | ######   #######  ##     ## ######## ##     ## ########                                      |\n");
    printf(" #@@@ @@@@ #@@* *@@@ @@@= @@@#  |                                                                                              |\n");
    printf(" #@@@@@@@@ #@@* *@@@ @@@= @@@#  |##     ##    ###    ##    ##    ###     ######   ######## ##     ## ######## ##    ## ########|\n");
    printf(" #@@=  @@@ #@@@# +@@ @@@= @@@#  |###   ###   ## ##   ###   ##   ## ##   ##    ##  ##       ###   ### ##       ###   ##    ##   |\n");
    printf(" #@@=  @@@ *@@@@@. = @@@= @@@#  |#### ####  ##   ##  ####  ##  ##   ##  ##        ##       #### #### ##       ####  ##    ##   |\n");
    printf(" #@@@  @@@ = -#@@@@= @@@= @@@#  |## ### ## ##     ## ## ## ## ##     ## ##   #### ######   ## ### ## ######   ## ## ##    ##   |\n");
    printf(" #@@@@@@@@ #@#  @@@@ @@@= @@@#  |##     ## ######### ##  #### ######### ##    ##  ##       ##     ## ##       ##  ####    ##   |\n");
    printf(" #@@=  @@@ #@@* *@@@ @@@= @@@#  |##     ## ##     ## ##   ### ##     ## ##    ##  ##       ##     ## ##       ##   ###    ##   |\n");
    printf("  #@@@@@#  #@@* *@@@ @@@@@@@#	|##     ## ##     ## ##    ## ##     ##  ######   ######## ##     ## ######## ##    ##    ##   |\n");
    printf("   *= #@@@ #@@* *@@@ @@@@@@*    |                                                                                              |\n");
    printf("       @@@ #@@* *@@@ @@@@#      | ######  ##    ##  ######  ######## ######## ##     ##                                        |\n");
    printf("       +#@ #@@@@@@@@ @#+        |##    ##  ##  ##  ##    ##    ##    ##       ###   ###                                        |\n");
    printf("            :=**+=:             |##         ####   ##          ##    ##       #### ####                                        |\n");
    printf("                                | ######     ##     ######     ##    ######   ## ### ##                                        |\n");
    printf("                                |      ##    ##          ##    ##    ##       ##     ##                                        |\n");
    printf("                                |##    ##    ##    ##    ##    ##    ##       ##     ##                                        |\n");
    printf("                                | ######     ##     ######     ##    ######## ##     ##                                        |\n");
    printf("                                +==============================================================================================+\n");

}