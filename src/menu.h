#pragma once


/* ─── Menu & CLI Control ─────────────────────────────────────── */

/* Prints the main menu options to stdout */
void displayMainMenu(void);

/* Reads user choice and dispatches to appropriate diary function */
void handleUserChoice(int choice);

/* Prints and handles the search sub-menu (by date or keyword) */
void displaySearchMenu(void);


