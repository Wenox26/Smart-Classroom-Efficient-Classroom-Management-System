#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100

void saveSchedule() {
    FILE *file = fopen("schedule.txt", "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    char day[20], schedule[MAX_LENGTH];
    printf("Enter the day (e.g., Monday): ");
    scanf("%s", day);
    getchar(); // Consume newline character
    printf("Enter the schedule: ");
    fgets(schedule, MAX_LENGTH, stdin);

    fprintf(file, "%s: %s", day, schedule);
    fclose(file);
    printf("Schedule saved successfully!\n");
}

void viewAllSchedules() {
    FILE *file = fopen("schedule.txt", "r");
    if (file == NULL) {
        printf("No schedules found!\n");
        return;
    }

    char line[MAX_LENGTH];
    printf("\nAll Schedules:\n");
    while (fgets(line, MAX_LENGTH, file)) {
        printf("%s", line);
    }
    fclose(file);
}

void viewSpecificSchedule() {
    FILE *file = fopen("schedule.txt", "r");
    if (file == NULL) {
        printf("No schedules found!\n");
        return;
    }

    char day[20], line[MAX_LENGTH];
    int found = 0;
    printf("Enter the day to view schedule: ");
    scanf("%s", day);

    while (fgets(line, MAX_LENGTH, file)) {
        if (strstr(line, day) != NULL) {
            printf("%s", line);
            found = 1;
        }
    }
    fclose(file);
    if (!found) {
        printf("No schedule found for %s!\n", day);
    }
}

int main() {
    int choice;
    do {
        printf("\nClassroom Management System\n");
        printf("1. Save Schedule\n");
        printf("2. View All Schedules\n");
        printf("3. View Specific Day Schedule\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

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
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}
