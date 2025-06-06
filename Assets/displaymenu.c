#include <stdio.h>

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
        
    switch (choice) {
        
        case 1:
            printf("\n                                [New Schedule Functionality]\n");
            break;
        case 2:
            printf("\n                                [Display All Schedules Functionality]\n");
            break;
        case 3:
            printf("\n                                [Display Day Schedule Functionality]\n");
            break;
        case 4:
            printf("\n                                Exiting the program...\n");
            break;
        default:
            printf("\n                                Invalid choice! Please try again.\n");
        }

    
    } while (choice >= 5 || choice == 0);


    return 0;
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