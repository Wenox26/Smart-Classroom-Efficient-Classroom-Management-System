#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100

void asciiArt();
int isTimeOverlapping(const char *filename, const char *newTime);
void saveSchedule();
void viewAllSchedules();
void viewSpecificSchedule();







int main() {

    int choice;
    
    asciiArt();
    
   //32 blank spaces

    do
    {
        
    
    
    printf("\n\n                                ================================================================================================\n");
    printf("                                |                           COMPUTER LABORATORY SCHEDULE MENU                                  |\n");
    printf("                                ================================================================================================\n");
    printf("                                | 1. New Schedule                                 3. Display Specific Day Schedule             |\n");
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
        printf("                                Thank you for using COMLAB MANAGEMENT SYSTEM\n");
        break;
    } else {
        printf("                                Invalid choice! Please try again.\n");
    }
        


    
    } while (choice != 4 || choice == 0);


    return 0;
}









//FUNCTIONS==========================================================================

//Checng overlapping schedules
int isTimeOverlapping(const char *filename, const char *newTime) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return 0; // No existing schedules, no overlap
    }

    char line[MAX_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "                                Time Schedule:")) {
            if (strstr(line, newTime)) {
                fclose(file);
                return 1; // Overlapping schedule found
            }
        }
    }
    fclose(file);
    return 0; // No overlap found
}


// Creating Schedules
void saveSchedule() {
    char day[20], schedule1[MAX_LENGTH];
    char sub[20], schedule2[MAX_LENGTH];
    char section[20], schedule3[MAX_LENGTH];
    int roomNumber;

    printf("                                Enter the day (Monday, Tuesday, Thursday, Friday): ");
    scanf("%s", day);
    getchar(); // Newline character

    printf("                                Select Computer Laboratory (1 to 5): ");
    scanf("%d", &roomNumber);
    getchar(); // Newline character

    if (roomNumber < 1 || roomNumber > 5) {
        printf("                                Invalid Computer Laboratory number!\n");
        return;
    }

    char filename[50];
    snprintf(filename, sizeof(filename), "%s_COMLAB%d.txt", day, roomNumber);

    printf("                                Enter the time schedule: ");
    fgets(schedule1, MAX_LENGTH, stdin);
    schedule1[strcspn(schedule1, "\n")] = 0;

    if (isTimeOverlapping(filename, schedule1)) {
        printf("                                Time schedule overlaps with an existing schedule.\n");
        return;
    }

    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("                                Error opening file!\n");
        return;
    }

    fprintf(file, "\n                                Time Schedule: %s\n", schedule1);

    printf("                                Enter the Subject: ");
    fgets(schedule2, MAX_LENGTH, stdin);
    fprintf(file, "                                Subject: %s", schedule2);

    printf("                                Enter the Section: ");
    fgets(schedule3, MAX_LENGTH, stdin);
    fprintf(file, "                                Section: %s", schedule3);

    fclose(file);
    printf("                                Schedule saved successfully for %s in COMLAB%d!\n", day, roomNumber);
}

// Viewing all Schedules
void viewAllSchedules() {
    char *days[] = {"Monday", "Tuesday", "Thursday", "Friday"};
    char filename[50], line[MAX_LENGTH];

    printf("\n                                All Schedules:\n");
    for (int i = 0; i < 4; i++) {
        for (int lab = 1; lab <= 5; lab++) {
            snprintf(filename, sizeof(filename), "%s_COMLAB%d.txt", days[i], lab);

            FILE *file = fopen(filename, "r");
            if (file != NULL) {
                printf("\n%s - COMLAB%d:\n", days[i], lab);
                while (fgets(line, MAX_LENGTH, file)) {
                    printf("%s", line);
                }
                fclose(file);
            }
        }
    }
}

// Viewing specific day and lab schedule
void viewSpecificSchedule() {
    char day[20], filename[50], line[MAX_LENGTH];
    int roomNumber;

    printf("                                Enter the day to view schedule (Monday, Tuesday, Thursday, Friday): ");
    scanf("%s", day);

    printf("                                Enter the Computer Room number (1 to 5): ");
    scanf("%d", &roomNumber);

    if (roomNumber < 1 || roomNumber > 5) {
        printf("                                Invalid room number!\n");
        return;
    }

    snprintf(filename, sizeof(filename), "%s_COMLAB%d.txt", day, roomNumber);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("                                No schedules found for %s in COMLAB%d!\n", day, roomNumber);
        return;
    }

    printf("\n                                Schedule for %s - COMLAB%d:\n", day, roomNumber);
    while (fgets(line, MAX_LENGTH, file)) {
        printf("%s", line);
    }
    fclose(file);
}










//Ascii art for display menu
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