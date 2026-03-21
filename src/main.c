#include "menu.h"
#include "file_handler.h"
#include "diary.h"
#include "utils.h"

int main(){
    int choice;
    while (1){
    displayMainMenu();
    choice = readMenuChoice();
    if (choice == -1) {
        app("Invalid input. Enter a number.");
        continue;
    }
    if(choice == 0){
        clearScreen();
        
        app("Exiting App.\n\tThank you for your time.\n");
        break;
    }
    else{
        handleUserChoice(choice);
    }
    printf("Press Enter to continue...");

    // Loop until the user presses Enter
    while (getchar() != '\n'); 
    clearScreen();
    showDots("loading...", 5,1);
    clearScreen();
    }
    return 0;
}