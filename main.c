#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100

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

    printf("Enter the day (Monday, Tuesday, Thursday, Friday): ");
    scanf("%s", day);
    getchar(); // Consume newline character

    char filename[30];
    strcpy(filename, day);
    strcat(filename, ".txt");

    printf("Enter the time schedule: ");
    fgets(schedule1, MAX_LENGTH, stdin);
    schedule1[strcspn(schedule1, "\n")] = 0; // Remove newline character

    if (isTimeOverlapping(filename, schedule1)) {
        printf("Already reserved to section --\n");
        return;
    }

    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    // SCHEDULING
    fprintf(file, "\nTime Schedule: %s\n", schedule1);

    printf("Enter the Subject: ");
    fgets(schedule2, MAX_LENGTH, stdin);
    fprintf(file, "Subject: %s", schedule2);

    printf("Enter the Section: ");
    fgets(schedule3, MAX_LENGTH, stdin);
    fprintf(file, "Section: %s", schedule3);

    fclose(file);

    printf("Schedule saved successfully for %s!\n", day);
}

int main() {
    int choice;
    do {
        printf("\nClassroom Management System\n");
        printf("1. Save Schedule\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            saveSchedule();
        } else if (choice == 2) {
            printf("Exiting...\n");
        } else {
            printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 2);

    return 0;
}
