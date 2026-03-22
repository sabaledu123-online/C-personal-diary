#pragma once

// constants used.

#define MAX_TITLE_LEN 100
#define MAX_CONTENT_LEN 2000
#define DATA_FILE "data/diary.dat"
#define MAX_ENTRIES 30

// Structs

typedef struct
{
    int day;
    int month;
    int year;
    int hour;
    int minute;
} DiaryDate;

typedef struct
{
    int id;
    char title[MAX_TITLE_LEN];
    char content[MAX_CONTENT_LEN];
    DiaryDate date;
    int is_deleted;
    // 0 = active & 1 = soft-deleted (not truly deleted but deactivated)
} DiaryEntry;

// -- core operations --

// gets details about , Title and content from user and saves it to our file.
// uses saveNewEntry() for saving to file.
void addEntry(void);

/*
    shows all the entries present with is_Deleted set to 0 .
    if is_deleted = 1 (set to 1) : considered deleted (soft-deleting)
    thus skipped in display.
 */

void viewEntries(void);

// Search By date (display all matching entries)
void searchByDate(DiaryDate target);

// search and display all entries containing the given keyword.
void searchByKeyword(const char *keyword);

// search that one particular entry (as ID -> unique to each entry.)
void searchByID(const int ID);

// get's entry by id (well search for it first then enter the ID I guess :( )
// Could use the serach feautre's help for improvement.
void editEntry(int id);

/*
    sets is_deleted = 1 ,
    doesn't actually delete the record/entry from file
    but just deactivates it for search , edit operations.
*/

void deleteEntry(int id);
