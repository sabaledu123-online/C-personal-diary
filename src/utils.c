#include "./utils.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
    #include <windows.h>   /* Sleep()  */
#else
    #include <unistd.h>    /* usleep() */
#endif

#include <stdlib.h>        /* system(), strtol() */

/* ─── Input Handling ─────────────────────────────────────────── */

void clearInputBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void readLine(char *buf, int max_len)
{
    if (fgets(buf, max_len, stdin) != NULL)
    {
        size_t len = strlen(buf);

        if (len > 0 && buf[len - 1] == '\n')
            buf[len - 1] = '\0';
    }
}

//  :: Validation ::

int validateTitle(const char *title) {
    if (title == NULL) return 0;
    size_t len = strlen(title);
    return (len > 0 && len <= MAX_TITLE_LEN - 1);
}

/* Returns 1 if the given ID exists and is not deleted */
int isValidActiveId(int id)
{
    if (id <= 0)
        return 0;

    FILE *fp = fopen(DATA_FILE, "rb");
    if (!fp)
        return 0;

    DiaryEntry entry;
    int found = 0;

    while (fread(&entry, sizeof(DiaryEntry), 1, fp) == 1)
    {
        if (entry.id == id && entry.is_deleted == 0)
        {
            found = 1;
            break;
        }
    }

    fclose(fp);
    return found;
}

// :: Date & Time

// fills the current date and time in the date in the diary date.
DiaryDate getCurrentDate(void)
{
    DiaryDate d;
    time_t now = time(NULL);
    struct tm *local = localtime(&now);

    d.year = local->tm_year + 1900;
    d.month = local->tm_mon + 1;
    d.day = local->tm_mday;
    d.hour = local->tm_hour;
    d.minute = local->tm_min;
    return d;
}

// Checks for matching of day/month/year of two diary entries.
int datesMatch(DiaryDate a, DiaryDate b)
{
    if (a.year == b.year &&
        a.month == b.month &&
        a.day == b.day)
        return 1;
    else
        return 0;
}

/* ─── Display Formatting ─────────────────────────────────────── */

void displayTitle(const char *title)
{
    int totalWidth = 50;
    int len = (int)strlen(title);

    // Top border
    printSeparator(2, totalWidth); // '-' style

    // If too long, print title as it is.
    if (len >= totalWidth - 6) // accounting for "::  ::"
    {
        printf(":: %s ::\n", title);
        printSeparator(2, totalWidth);
        return;
    }

    int innerWidth = totalWidth - 6; // space inside "::  ::"
    int leftPadding = (innerWidth - len) / 2;
    int rightPadding = innerWidth - len - leftPadding;

    printf(":: %*s%s%*s ::\n",
        leftPadding, "",
        title,
        rightPadding, "");

    // Bottom border
    printSeparator(2, totalWidth);
}

/* Prints a single DiaryEntry in formatted layout */
void printEntry(const DiaryEntry *entry)
{
    printSeparator(1, 20);
    printf("  ID      : %d\n", entry->id);
    printf("  Title   : %s\n", entry->title);
    printf("  Date    : %02d/%02d/%04d  %02d:%02d\n",
        entry->date.day, entry->date.month, entry->date.year,
        entry->date.hour, entry->date.minute);
    printSeparator(3, strlen(entry->content)+2);
    printf("\n %s\n", entry->content);
    printSeparator(3, strlen(entry->content)+2);
    putchar('\n');
}

/* Prints a visual separator line */

void printSeparator(int symbolIndex, int width)
{

    char symbols[] = {'_', '*', '-', '=', '#', '.', '~', ':', '|', '+', '>', '/'};

    // Safety check for array bounds
    if (symbolIndex < 0 || symbolIndex >= 12)
        symbolIndex = 2; // Default to '-'
    for (int j = 0; j < width; j++)
    {
        putchar(symbols[symbolIndex]);
    }
    putchar('\n'); // Move to next line after printing
}

// decorative separator
void decSeparator(int index, int repeats)
{
    const char *patterns[] = {
        "<>",  // 0
        "-x-", // 1
        "^-^", // 2
        "=-=", // 3
        "~_~"  // 4
    };

    if (index < 0 || index >= 5)
        index = 0; // Default safety (for array out of bounds)
    printf("\n");
    for (int i = 0; i < repeats; i++)
    {
        printf("%s", patterns[index]);
    }
    printf("\n");
}

void app(const char *info)
{
    printf("App:");
    printf("\n\t%s\n", info);
}

void showDots(const char *msg, int count, int delay_sec) {
    printf("  %s", msg);
    fflush(stdout);

    for (int i = 0; i < count; i++) {
        #ifdef _WIN32
            Sleep(delay_sec*1000);
        #else
            usleep((useconds_t)(delay_sec * 1000));
        #endif
        printf(".");
        fflush(stdout);
    }
    printf("\n");
}

void clearScreen(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int readMenuChoice(void) {
    char buf[16];
    if (fgets(buf, sizeof(buf), stdin) == NULL)
        return -1;

    char *end;
    long val = strtol(buf, &end, 10);

    if (end == buf || (*end != '\n' && *end != '\0'))
        return -1;

    return (int)val;
}