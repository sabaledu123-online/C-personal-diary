#pragma once


#include "diary.h"

/* ─── Input Handling ─────────────────────────────────────────── */

/* Flushes remaining characters from stdin */
void clearInputBuffer(void);

/* Safe string input: reads at most (max_len - 1) chars into buf */
void readLine(char *buf, int max_len);

/* ─── Validation ─────────────────────────────────────────────── */

/* Returns 1 if title is non-empty and within MAX_TITLE_LEN */
int  validateTitle(const char *title);

/* Returns 1 if the given ID exists and is not deleted */
int  isValidActiveId(int id);

/* ─── Date & Time ────────────────────────────────────────────── */

/* Populates a DiaryDate with the current system time */
DiaryDate getCurrentDate(void);

/* Returns 1 if two DiaryDate structs match on day/month/year */
int  datesMatch(DiaryDate a, DiaryDate b);

/* ─── Display Formatting ─────────────────────────────────────── */

/* Prints a single DiaryEntry in formatted layout */
void printEntry(const DiaryEntry *entry);

/* Prints a visual separator line */
void printSeparator(int symbolIndex, int width );

void decSeparator(int index, int repeats);

void app(const char* info);

void displayTitle(const char *title);

void showDots(const char *msg, int count, int delay_sec);

void clearScreen(void);

int readMenuChoice(void);