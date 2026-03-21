#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "diary.h"
#include "file_handler.h"
#include "utils.h"

// Helper function : For Input Handling
static void get_input(char *buffer, int size, const char *prompt)
{
    printf("%s", prompt);

    if (fgets(buffer, size, stdin) != NULL)
    {
        // Check if the newline exists
        char *nl = strchr(buffer, '\n');

        if (nl)
        {
            *nl = '\0'; // Standard case: remove the newline
        }
        else
        {
            // Over-limit case: The newline is still in the 'stdin' pipe.
            // We must loop through and "eat" the remaining chars.
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
                ;
        }
    }
}

/* ─── Core Operations ────────────────────────────────────────── */

/* Collects title + content from user, assigns ID, persists to file */
void addEntry(void)
{
    DiaryEntry entry;
    memset(&entry, 0, sizeof(DiaryEntry));

    entry.id = getNextId();
    entry.date = getCurrentDate();
    entry.is_deleted = 0;

    int response;
    displayTitle("New Diary Entry");
    printSeparator(1,20);
    printf("(1) Entry ID: %d\n", entry.id);
    do
    {
        get_input(entry.title, MAX_TITLE_LEN, "(2) Title    : ");
        if (!validateTitle(entry.title))
            printf("App: \n\tTitle cannot be empty. \n\tTry again.\n");
    } while (!validateTitle(entry.title));
    get_input(entry.content, MAX_CONTENT_LEN, "(3) Details: \n\t");
do
    {
        printf("\nDo you wish to add this entry?\n Yes -> 1\n No -> 2\n>>> ");
        scanf("%d", &response);
        clearInputBuffer();

        if (response == 1)
        {
            saveNewEntry(&entry);
            app("Entry successfully added!\n");
        }
        else if (response == 2)
        {
            app("Request cancelled. Entry was not added.\n");
        }
        else
        {
            app("Invalid response. Enter 1 or 2.\n");
        }
    } while (response != 1 && response != 2);
}

/* ─── View All Entries ───────────────────────────────────────── */

void viewEntries(void)
{
    DiaryEntry entries[MAX_ENTRIES];
    int total = loadAllEntries(entries, MAX_ENTRIES);
    int found = 0;

    displayTitle("All Entries");

    for (int i = 0; i < total; i++)
    {
        if (entries[i].is_deleted == 0)
        {
            printEntry(&entries[i]);
            found++;
        }
    }

    if (found == 0)
        printf("App: \n\tNo entries found.\n\n");
    else
        printf("  %d entr%s found.\n\n", found, found == 1 ? "y" : "ies");
}

// Search By date

void searchByDate(DiaryDate target)
{
    DiaryEntry entries[MAX_ENTRIES];
    int total = loadAllEntries(entries, MAX_ENTRIES);
    int found = 0;

    displayTitle("Search by Date");

    for (int i = 0; i < total; i++)
    {
        if (entries[i].is_deleted == 0 && datesMatch(entries[i].date, target))
        {
            printEntry(&entries[i]);
            found++;
        }
    }

    if (found == 0)
        printf("App:\n\tNo entries for %02d/%02d/%04d.\n\n",
            target.day, target.month, target.year);
    else
        printf("  %d entr%s found.\n\n", found, found == 1 ? "y" : "ies");
}

// Search By keyword

void searchByKeyword(const char *keyword)
{
    DiaryEntry entries[MAX_ENTRIES];
    int total = loadAllEntries(entries, MAX_ENTRIES);
    int found = 0;

    displayTitle("Search by Keyword");

    for (int i = 0; i < total; i++)
    {
        if (entries[i].is_deleted == 1)
            continue;

        int inTitle = strstr(entries[i].title, keyword) != NULL;
        int inContent = strstr(entries[i].content, keyword) != NULL;

        if (inTitle || inContent)
        {
            printEntry(&entries[i]);
            found++;
        }
    }

    if (found == 0)
        printf("   No entries matching \"%s\".\n\n", keyword);
    else
        printf("  %d entr%s found.\n\n", found, found == 1 ? "y" : "ies");
}

/* ─── Search by ID ───────────────────────────────────────────── */

void searchByID(const int ID)
{
    DiaryEntry entries[MAX_ENTRIES];
    int total = loadAllEntries(entries, MAX_ENTRIES);

    displayTitle("Search by ID");

    for (int i = 0; i < total; i++)
    {
        if (entries[i].id == ID && entries[i].is_deleted == 0)
        {
            printEntry(&entries[i]);
            return;
        }
    }

    printf("App: \n\tNo active entry with ID : %d.\n\n", ID);
}

/* ─── Edit Entry ─────────────────────────────────────────────── */

void editEntry(int id)
{
    DiaryEntry entries[MAX_ENTRIES];
    int total = loadAllEntries(entries, MAX_ENTRIES);

    displayTitle("Edit Entry");

    for (int i = 0; i < total; i++)
    {
        if (entries[i].id == id && entries[i].is_deleted == 0)
        {

            // editing title
            printf("  Current Title   : %s\n", entries[i].title);
            printf("  New Title (press 'Enter' to keep):\n  >>> ");

            char newTitle[MAX_TITLE_LEN];

            if (fgets(newTitle, MAX_TITLE_LEN, stdin))
            {
                char *nl = strchr(newTitle, '\n');
                if (nl)
                {
                    *nl = '\0';
                }
            }
            // got a new title?? yes: copy paste to title else: skip
            if (strlen(newTitle) > 0)
                strncpy(entries[i].title, newTitle, MAX_TITLE_LEN - 1);

            // editing contents
            printf("\n  Current Content :\n  %s\n\n", entries[i].content);
            printf("  New Content (press 'Enter' to keep):\n  >>> ");

            char newContent[MAX_CONTENT_LEN];

            if (fgets(newContent, MAX_CONTENT_LEN, stdin))
            {
                char *nl = strchr(newContent, '\n');
                if (nl)
                    *nl = '\0';
            }
            // got new content?? yes: copy paste to content else: skip
            if (strlen(newContent) > 0)
                strncpy(entries[i].content, newContent, MAX_CONTENT_LEN - 1);

            entries[i].date = getCurrentDate();
            updateEntryById(&entries[i]);
            // goes to that specific id and updates in the memory (file)
            printf("Entry #%d updated successfully.\n\n", id);
            return;
        }
    }

    printf("App: \n\tNo active entry with ID %d.\n\n", id);
}

/* ─── Delete Entry ───────────────────────────────────────────── */

void deleteEntry(int id)
{
    DiaryEntry entries[MAX_ENTRIES];
    int total = loadAllEntries(entries, MAX_ENTRIES);

    for (int i = 0; i < total; i++)
    {
        if (entries[i].id == id && entries[i].is_deleted == 0)
        {

            printf("  [#] Delete entry #%d \"%s\"? (y/n): ",
                id, entries[i].title);

            char confirm;
            scanf(" %c", &confirm);
            clearInputBuffer();

            if (confirm == 'y' || confirm == 'Y')
            {
                entries[i].is_deleted = 1;
                updateEntryById(&entries[i]);
                printf("App: \n\tEntry #%d deleted.\n\n", id);
            }
            else
            {
                app(" Deletion cancelled.\n");
            }
            return;
        }
    }

    printf("No active entry with ID %d.\n\n", id);
}