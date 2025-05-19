#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100
#define MAX_SCHEDULES 100
#define MAX_LINE 300

// Define "Schedule" attributes
typedef struct {
    char timeRange[50];    // e.g., 7:30AM-10:00AM
    char subject[100];
    char section[100];
    int startHour24;
    int startMinute;
} Schedule;

//Display Menu Design
void asciiArt();

//Time Management
int isTimeOverlapping(const char *filename, const char *newStart, const char *newEnd, char *conflictSubject, char *conflictSection);
int convertToMinutes(const char *timeStr);
int compareTime(const void *a, const void *b);
void convertTo24Hour(const char *timeStr, int *hour, int *minute);
void extractStartTime(const char *timeRange, int *hour, int *minute);

//Create and Read Data
void saveSchedule();
void viewAllSchedules();
void viewSpecificSchedule();

int main() {

    asciiArt();

    int choice;
   
    do {
        printf("\n\n                                ================================================================================================\n");
        printf("                                |                           COMPUTER LABORATORY SCHEDULE MENU                                  |\n");
        printf("                                ================================================================================================\n");
        printf("                                | 1. New Schedule                                 3. Display Specific Day Schedule             |\n");
        printf("                                | 2. Display All Schedules                        4. Exit                                      |\n");
        printf("                                ================================================================================================\n");
        printf("\n                                Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // clear buffer

        switch (choice) {
            case 1:
                saveSchedule();
                break;
            case 2:
                viewAllSchedules();
                break;
            case 3:
                viewSpecificSchedule();
                break;
            case 4:
                printf("                                Thank you for using COMLAB MANAGEMENT SYSTEM\n");
                break;
            default:
                printf("                                Invalid choice! Please try again.\n");
                break;
        }
    } while (choice != 4);

    return 0;
}

// FUNCTIONS ==========================================================================

// Converts a time string (e.g., "7:30AM") to the total number of minutes since midnight
int convertToMinutes(const char *timeStr) {

    int hour, minute;
    char meridian[3];
    sscanf(timeStr, "%d:%d%2s", &hour, &minute, meridian);

    if ((meridian[0] == 'P' || meridian[0] == 'p') && hour != 12) hour += 12;
    if ((meridian[0] == 'A' || meridian[0] == 'a') && hour == 12) hour = 0;

    return hour * 60 + minute;
}

//It checks if two time ranges overlap.
int timesOverlap(const char *start1, const char *end1, const char *start2, const char *end2) {
    int s1 = convertToMinutes(start1);
    int e1 = convertToMinutes(end1);
    int s2 = convertToMinutes(start2);
    int e2 = convertToMinutes(end2);
    return (s1 < e2 && s2 < e1);
}

// Smarter overlap detection
int isTimeOverlapping(const char *filename, const char *newStart, const char *newEnd, char *conflictSubject, char *conflictSection) {
    FILE *file = fopen(filename, "r");
    if (!file) return 0;

    char line[256];
    char existingStart[MAX_LENGTH], existingEnd[MAX_LENGTH];
    char subject[100], section[100];

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "Time Schedule:") != NULL) {
            sscanf(line, "                                Time Schedule: %[^-]-%s", existingStart, existingEnd);

            fgets(line, sizeof(line), file);
            sscanf(line, "                                Subject: %[^\n]", subject);

            fgets(line, sizeof(line), file);
            sscanf(line, "                                Section: %[^\n]", section);

            if (timesOverlap(existingStart, existingEnd, newStart, newEnd)) {
                strcpy(conflictSubject, subject);
                strcpy(conflictSection, section);
                fclose(file);
                return 1;
            }
        }
    }

    fclose(file);
    return 0;
}

// Compare function for sorting
int compareTime(const void *a, const void *b) {
    Schedule *s1 = (Schedule *)a;
    Schedule *s2 = (Schedule *)b;

    if (s1->startHour24 != s2->startHour24) {
        return s1->startHour24 - s2->startHour24;
    }
    return s1->startMinute - s2->startMinute;
}

// Convert time string (like "7:30AM") to 24-hour format
void convertTo24Hour(const char *timeStr, int *hour, int *minute) {
    int h, m;
    char period[3];
    sscanf(timeStr, "%d:%d%2s", &h, &m, period);

    if ((strcmp(period, "PM") == 0 || strcmp(period, "pm") == 0) && h != 12) {
        h += 12;
    } else if ((strcmp(period, "AM") == 0 || strcmp(period, "am") == 0) && h == 12) {
        h = 0;
    }

    *hour = h;
    *minute = m;
}

// Extracts start time from "7:30AM-10:00AM"
void extractStartTime(const char *timeRange, int *hour, int *minute) {
    char startTime[20];
    sscanf(timeRange, "%[^-]", startTime);
    convertTo24Hour(startTime, hour, minute);
}


//SCHEDULE CREATE AND READ
// Creating Schedules
void saveSchedule() {
    char day[20], start[MAX_LENGTH], end[MAX_LENGTH];
    char subject[100];
    char section[100];
    int roomNumber;

    printf("                                Select Computer Laboratory (1 to 5): ");
    scanf("%d", &roomNumber);
    getchar(); // Clear newline

    if (roomNumber < 1 || roomNumber > 5) {
        printf("                                Invalid Computer Laboratory number!\n");
        return;
    }

    printf("                                Enter the day (Monday, Tuesday, Wednesday[Makeup Class] Thursday, Friday): ");
    scanf("%s", day);
    getchar();

    if (strcmp(day, "Saturday") == 0 || strcmp(day, "saturday") == 0 || strcmp(day, "Sunday") == 0   || strcmp(day, "sunday") == 0) {
    printf("                                Error: Scheduling is not allowed on Saturdays and Sundays.\n");
    return;
    }   
    
    char filename[50];
    snprintf(filename, sizeof(filename), "COMLAB%d_%s.txt", roomNumber, day);

    
    printf("                                Enter the start time (e.g., 7:30AM): ");
    fgets(start, MAX_LENGTH, stdin);
    start[strcspn(start, "\n")] = 0; // Remove newline

    printf("                                Enter the end time (e.g., 10:00AM): ");
    fgets(end, MAX_LENGTH, stdin);
    end[strcspn(end, "\n")] = 0;

    char fullTime[MAX_LENGTH];
    snprintf(fullTime, sizeof(fullTime), "%s-%s", start, end);

    
    char conflictSubject[100]="";
    char conflictSection[100]="";

    
    if (isTimeOverlapping(filename, start, end, conflictSubject, conflictSection)) {
        printf("\n                                Time schedule overlaps with an existing schedule.\n");
        printf("                                Conflicting Subject: %s\n", conflictSubject);
        printf("                                Conflicting Section: %s\n", conflictSection);
        return;
    }

    printf("                                Enter the Subject: ");
    fgets(subject, sizeof(subject), stdin);
    subject[strcspn(subject, "\n")] = 0;

    printf("                                Enter the Section: ");
    fgets(section, sizeof(section), stdin);
    section[strcspn(section, "\n")] = 0;
    

    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("                                Error opening file!\n");
        return;
    }

    fprintf(file, "                                Time Schedule: %s\n", fullTime);
    fprintf(file, "                                Subject: %s\n", subject);
    fprintf(file, "                                Section: %s\n\n", section);

    fclose(file);
    printf("                                Schedule saved successfully for COMLAB%d in %s!\n", roomNumber, day);
}

// Viewing all Schedules
void viewAllSchedules() {
    char *days[] = {"Monday", "Tuesday", "Thursday", "Friday"};
    char filename[50], line[MAX_LINE];

    printf("\n                                All Schedules:\n");

    for (int lab = 1; lab <= 5; lab++) {
        for (int d = 0; d < 4; d++) {
            snprintf(filename, sizeof(filename), "COMLAB%d_%s.txt", lab, days[d]);
            FILE *file = fopen(filename, "r");

            if (file != NULL) {
                Schedule list[MAX_SCHEDULES];
                int count = 0;

                while (fgets(line, sizeof(line), file)) {
                    if (strstr(line, "Time Schedule:")) {
                        sscanf(line, "                                Time Schedule: %[^\n]", list[count].timeRange);
                        fgets(line, sizeof(line), file);
                        sscanf(line, "                                Subject: %[^\n]", list[count].subject);
                        fgets(line, sizeof(line), file);
                        sscanf(line, "                                Section: %[^\n]", list[count].section);

                        extractStartTime(list[count].timeRange, &list[count].startHour24, &list[count].startMinute);
                        count++;
                    }
                }
                fclose(file);

                if (count > 0) {
                    printf("\n                                    COMLAB%d - %s:\n", lab, days[d]);

                    qsort(list, count, sizeof(Schedule), compareTime);

                    for (int i = 0; i < count; i++) {
                        printf("                                    Time Schedule: %s\n", list[i].timeRange);
                        printf("                                    Subject: %s\n", list[i].subject);
                        printf("                                    Section: %s\n\n", list[i].section);
                    }
                }
            }
        }
    }
}

// Viewing specific day and lab schedule
void viewSpecificSchedule() {
    char day[20], filename[50], line[MAX_LINE];
    int roomNumber;

    printf("                                Enter the Computer Room number (1 to 5): ");
    scanf("%d", &roomNumber);
    getchar();

    printf("                                Enter the day to view schedule (Monday, Tuesday, Wednesday[Makeup Class] Thursday, Friday): ");
    scanf("%s", day);
    getchar();

    if (roomNumber < 1 || roomNumber > 5) {
        printf("                                Invalid room number!\n");
        return;
    }

    snprintf(filename, sizeof(filename), "COMLAB%d_%s.txt", roomNumber, day);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("                                No schedules found for %s in COMLAB%d!\n", day, roomNumber);
        return;
    }

    Schedule list[MAX_SCHEDULES];
    int count = 0;

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "Time Schedule:")) {
            sscanf(line, "                                Time Schedule: %[^\n]", list[count].timeRange);
            fgets(line, sizeof(line), file);
            sscanf(line, "                                Subject: %[^\n]", list[count].subject);
            fgets(line, sizeof(line), file);
            sscanf(line, "                                Section: %[^\n]", list[count].section);

            extractStartTime(list[count].timeRange, &list[count].startHour24, &list[count].startMinute);
            count++;
        }
    }
    fclose(file);

    if (count == 0) {
        printf("                                No schedules available for %s in COMLAB%d!\n", day, roomNumber);
        return;
    }

    //Sorting schedules
    qsort(list, count, sizeof(Schedule), compareTime);

    printf("\n                                Schedule for %s - COMLAB%d:\n\n", day, roomNumber);
    
    for (int i = 0; i < count; i++) {
        printf("                                    Time Schedule: %s\n", list[i].timeRange);
        printf("                                    Subject: %s\n", list[i].subject);
        printf("                                    Section: %s\n\n", list[i].section);
    }
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
