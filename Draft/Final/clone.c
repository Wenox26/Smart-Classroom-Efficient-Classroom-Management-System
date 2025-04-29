#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100
#define MAX_SCHEDULES 100
#define MAX_LINE 300

// Define "Schedule" structure
typedef struct {
    char timeRange[50];    // e.g., 7:30AM-10:00AM
    char subject[100];
    char section[100];
    int startHour24;
    int startMinute;
} Schedule;

void asciiArt();

int isTimeOverlapping(const char *filename, const char *newTime, const char *newEndtime);
int timeToMinutes(const char *timeStr);

void saveSchedule();
void viewAllSchedules();
void viewSpecificSchedule();
int compareTime(const void *a, const void *b);
void convertTo24Hour(const char *timeStr, int *hour, int *minute);
void extractStartTime(const char *timeRange, int *hour, int *minute);

int main() {
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
int timeToMinutes(const char *timeStr) {
    int hour, minute;
    char period[3];
    sscanf(timeStr, "%d:%d%2s", &hour, &minute, period);

    if ((strcmp(period, "PM") == 0 || strcmp(period, "pm") == 0) && hour != 12) {
        hour += 12;
    } else if ((strcmp(period, "AM") == 0 || strcmp(period, "am") == 0) && hour == 12) {
        hour = 0;
    }

    return hour * 60 + minute;
}


// Smarter overlap detection
int isTimeOverlapping(const char *filename, const char *newStartTime, const char *newEndTime) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return 0;
    }

    int newStart = timeToMinutes(newStartTime);
    int newEnd = timeToMinutes(newEndTime);

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "Time Schedule:")) {
            char existingRange[MAX_LENGTH];
            sscanf(line, "                                Time Schedule: %[^\n]", existingRange);

            char existingStart[20], existingEnd[20];
            sscanf(existingRange, "%[^-]-%s", existingStart, existingEnd);

            int existStart = timeToMinutes(existingStart);
            int existEnd = timeToMinutes(existingEnd);

            // Check if overlapping
            if (newStart < existEnd && existStart < newEnd) {
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

    printf("                                Enter the day (Monday, Tuesday, Thursday, Friday): ");
    scanf("%s", day);
    getchar();

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

    if (isTimeOverlapping(filename, start, end)) {
        printf("                                Time schedule overlaps with an existing schedule.\n");
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

    printf("                                Enter the day to view schedule (Monday, Tuesday, Thursday, Friday): ");
    scanf("%s", day);
    getchar();

    printf("                                Enter the Computer Room number (1 to 5): ");
    scanf("%d", &roomNumber);
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

    qsort(list, count, sizeof(Schedule), compareTime);

    printf("\n                                Schedule for %s - COMLAB%d:\n\n", day, roomNumber);
    for (int i = 0; i < count; i++) {
        printf("                                    Time Schedule: %s\n", list[i].timeRange);
        printf("                                    Subject: %s\n", list[i].subject);
        printf("                                    Section: %s\n\n", list[i].section);
    }
}





