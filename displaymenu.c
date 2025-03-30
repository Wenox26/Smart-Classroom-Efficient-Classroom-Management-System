int main() {
    int choice;
    
    do {
        printf("\n");
        printf("      ____________________\n");
        printf("     |                    |\n");
        printf("     |   COMPUTER LAB     |\n");
        printf("     |   SCHEDULE SYSTEM  |\n");
        printf("     |____________________|\n");
        printf("          ||      ||\n");
        printf("          ||      ||\n");
        printf("          ||______||\n");
        printf("          |______|\n");
        printf("\n");
        printf("====================================\n");
        printf("|     COMPUTER LAB SCHEDULE MENU   |\n");
        printf("====================================\n");
        printf("| 1. New Schedule                 |\n");
        printf("| 2. Display All Schedules        |\n");
        printf("| 3. Display Day Schedule         |\n");
        printf("| 4. Exit                         |\n");
        printf("====================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("\n[New Schedule Functionality]\n");
                break;
            case 2:
                printf("\n[Display All Schedules Functionality]\n");
                break;
            case 3:
                printf("\n[Display Day Schedule Functionality]\n");
                break;
            case 4:
                printf("\nExiting the program...\n");
                break;
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    } while (choice != 4);
    
    return 0;
}