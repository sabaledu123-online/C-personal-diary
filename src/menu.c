#include <stdio.h>
#include "./menu.h"
#include "./utils.h"
#include <string.h>
#include "diary.h"
#include <time.h>
/*
    For printSeparator:

        {'_', '*', '-', '=', '#', '.', '~', ':', '|', '+', '>', '/'}
        Range : 0-11 (for index)

    For decSeparator:
        "<>",  // 0
        "-x-", // 1
        "^-^", // 2
        "=-=", // 3
        "~_~"  // 4

*/
int validateDate(DiaryDate *check){
    time_t now = time(NULL);
    struct tm *today = localtime(&now);

    if(
        check->day >31 ||check->day<1||
        check->month > 12|| check->month <1 ||
        check->year > today->tm_year+1900
    )
    {
        return 0;
    }else if(
        check->year <= today->tm_year+1900 && 
        check->month<= today->tm_mon+1  &&
    check->day<=today->tm_mday){
        return 1;
    }
}




// Display the main menu.
void displayMainMenu(void){
    displayTitle("--Main Menu--");

    printf(""
        "[1]  Add Entry\n"
        "[2]  View All Entries\n"
        "[3]  Search Entries\n"
        "[4]  Edit / Update Entry\n"
        "[5]  Delete Entry\n"
        "[0]  Exit\n");
    printSeparator(2, 20);
    printf("\nResponse: ");
}

void handleUserChoice(int choice) {
    clearScreen();
    switch (choice) {

        case 1:
            addEntry();
            break;

        case 2:
            viewEntries();
            break;

        case 3: {
            int searchChoice;
            displaySearchMenu();
            searchChoice = readMenuChoice();
            if (searchChoice == -1) {
                app("Invalid input. Enter a number.");
                break;
            }

            if (searchChoice == 1) {
                /* Search by Date */
                DiaryDate target;
                clearScreen();
                retry:
                printf("  Enter date (YYYY MM DD): ");
                scanf(" %d %d %d", &target.year, &target.month, &target.day);
                clearInputBuffer();
                if(validateDate(&target) == 0){
                    printf("Invalid date entry.");
                    goto retry;
                }
                target.hour = 0; target.minute = 0;
                searchByDate(target);

            } else if (searchChoice == 2) {
                /* Search by ID */
                int id;
                clearScreen();
                printf("  Enter ID: ");
                scanf("%d", &id);
                clearInputBuffer();
                searchByID(id);

            } else if (searchChoice == 3) {
                char keyword[MAX_TITLE_LEN];
                clearScreen();
                printf("  Keyword: ");
                readLine(keyword, MAX_TITLE_LEN);
                searchByKeyword(keyword);
            } else if (searchChoice != 0) {
                app("Invalid search option.");
            }
            break;
        }

        case 4: {
            int id;
            printf("  Enter ID to edit: ");
            scanf("%d", &id);
            clearInputBuffer();
            editEntry(id);
            break;
        }

        case 5: {
            int id;
            printf("  Enter ID to delete: ");
            scanf("%d", &id);
            clearInputBuffer();
            deleteEntry(id);
            break;
        }

        case 0:
            printf("\n  Goodbye. Your diary has been saved.\n\n");
            break;

        default:
            app("Invalid choice. \n\tTry again.\n");
            break;
    }
}

/* Prints and handles the search sub-menu (by date or keyword) */
void displaySearchMenu(void){
    printSeparator(2, 20);
    displayTitle("-- Search For Entries --");
    printSeparator(2, 20);
    printf(
        "[1]  By Date\n"
        "[2]  By ID\n"
        "[3]  By Keyword\n"
        "[0]  Back to Main Menu\n"
    );
    printSeparator(2, 20);
    printf("\nResponse: ");
}

