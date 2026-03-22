#pragma once

#include "diary.h"

// Input handling

// flushes (kinda 'eats') remaining extra characters from stdin
void clearInputBuffer(void);

// for getting user input within max length.
void readLine(char *buf, int max_len);

//type safety for user input (to make sure user input is a valid NUMBER)
int readMenuChoice(void);

// -- validation --

// checks for empty title and and whether max_title length is exceeded.
int validateTitle(const char *title);

// checks for active status (is_deleted = 0) of ID and it's existence in the file.
int isValidActiveId(int id);

// -- Date and time --

// Adds current date and time in diary entry.
DiaryDate getCurrentDate(void);

// Checks the dates: year, month and day of two diary entries.
int datesMatch(DiaryDate a, DiaryDate b);

// -- Display and output formatting. --

//Prints a single diary entry in formatted manner
void printEntry(const DiaryEntry *entry);

//displays title in a well formatted manner with separtor lines included.
void displayTitle(const char *title);


//-- Separators --

//for general separator lines.
void printSeparator(int symbolIndex, int width);

//for decorative separators like <><><><> and so on.
void decSeparator(int index, int repeats);


//Miscellaneous (things I wanted to add for personal taste)
// ps: app() sucks to how it's currently used. : room for improvement.

//basically prints a message like success or error with an App: attached at first. 
// Haven't really utilized or used as I hoped to use it.
void app(const char *info);

// To show the loading..... effect with delay.
void showDots(const char *msg, int count, int delay_sec);

// To clear the screen for less clutter and information at once. 
void clearScreen(void);

