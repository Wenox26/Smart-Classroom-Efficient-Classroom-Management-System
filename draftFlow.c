#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100

void saveSchedule() {
    char day[20], schedule[MAX_LENGTH];
    printf("Enter the day (Monday, Tuesday, Thursday, Friday): ");
    scanf("%s", day);
    getchar(); // Consume newline character

    // Determine the file name based on the day
    char filename[30];
    snprintf(filename, sizeof(filename), "%s.txt", day);

    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter the schedule: ");
    fgets(schedule, MAX_LENGTH, stdin);

    fprintf(file, "%s\n", schedule);
    fclose(file);
    printf("Schedule saved successfully for %s!\n", day);
}

void viewAllSchedules() {
    const char *days[] = {"Monday", "Tuesday", "Thursday", "Friday"};
    char filename[30], line[MAX_LENGTH];

    printf("\nAll Schedules:\n");
    for (int i = 0; i < 4; i++) {
        snprintf(filename, sizeof(filename), "%s.txt", days[i]);
        FILE *file = fopen(filename, "r");
        if (file != NULL) {
            printf("\n%s:\n", days[i]);
            while (fgets(line, MAX_LENGTH, file)) {
                printf("%s", line);
            }
            fclose(file);
        } else {
            printf("\n%s: No schedules found!\n", days[i]);
        }
    }
}

void viewSpecificSchedule() {
    char day[20], filename[30], line[MAX_LENGTH];
    printf("Enter the day to view schedule (Monday, Tuesday, Thursday, Friday): ");
    scanf("%s", day);

    snprintf(filename, sizeof(filename), "%s.txt", day);
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("No schedules found for %s!\n", day);
        return;
    }

    printf("\nSchedule for %s:\n", day);
    while (fgets(line, MAX_LENGTH, file)) {
        printf("%s", line);
    }
    fclose(file);
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
