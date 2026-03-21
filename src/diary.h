#pragma once

/* ─── Constants ─────────────────────────────────────────────── */

#define MAX_TITLE_LEN    100
#define MAX_CONTENT_LEN  2000
#define DATA_FILE        "data/diary.dat"
#define MAX_ENTRIES      30

/* ─── Structs ────────────────────────────────────────────────── */

typedef struct {
    int day;
    int month;
    int year;
    int hour;
    int minute;
} DiaryDate;

typedef struct {
    int       id;
    char      title[MAX_TITLE_LEN];
    char      content[MAX_CONTENT_LEN];
    DiaryDate date;
    int       is_deleted;   /* 0 = active | 1 = soft-deleted */
} DiaryEntry;

/* ─── Core Operations ────────────────────────────────────────── */

/* Collects title + content from user, assigns ID, persists to file */
void addEntry(void);

/* Loads and displays all active (non-deleted) entries */
void viewEntries(void);

/* Finds and displays entries matching a date */
void searchByDate(DiaryDate target);

/* Finds and displays entries where title or content contains keyword */
void searchByKeyword(const char *keyword);

void searchByID(const int ID);

/* Locates entry by ID, prompts for new content, updates file */
void editEntry(int id);

/* Sets is_deleted = 1 for the given entry ID, updates file */
void deleteEntry(int id);
