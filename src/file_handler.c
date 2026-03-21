
#include <stdio.h>
#include "file_handler.h"

#include <direct.h>
#include <sys/stat.h>

static void ensureDataDir(void) {
#ifdef _WIN32
    _mkdir("data");
#else
    mkdir("data", 0755);
#endif
}

/* Reads all records into entries[], returns total count loaded */
int loadAllEntries(DiaryEntry entries[], int max) {
    FILE *fp = fopen(DATA_FILE, "rb");
    if (!fp) return 0;

    int count = 0;
    while (count < max && fread(&entries[count], sizeof(DiaryEntry), 1, fp) == 1)
        count++;

    fclose(fp);
    return count;
}

/* Appends a new entry to the end of the data file */
void saveNewEntry(const DiaryEntry *entry) {
    ensureDataDir();    
    FILE *fp = fopen(DATA_FILE, "ab");
    if (!fp) {
        fprintf(stderr, "[!] Error: Could not open file for writing.\n");
        return;
    }
    fwrite(entry, sizeof(DiaryEntry), 1, fp);
    fclose(fp);
}

/*
    Overwrites a single record in-place using fseek.
    Offset = (id - 1) * sizeof(DiaryEntry)
    IDs are 1-based, file records are 0-indexed.
*/
void updateEntryById(const DiaryEntry *entry) {
    FILE *fp = fopen(DATA_FILE, "r+b");
    if (!fp) {
        fprintf(stderr, "[!] Error: Could not open file for update.\n");
        return;
    }

    long offset = (long)(entry->id - 1) * (long)sizeof(DiaryEntry);
    fseek(fp, offset, SEEK_SET);
    fwrite(entry, sizeof(DiaryEntry), 1, fp);
    fclose(fp);
}

/* Returns total records in file including soft-deleted ones */
int getEntryCount(void) {
    FILE *fp = fopen(DATA_FILE, "rb");
    if (!fp) return 0;

    fseek(fp, 0, SEEK_END);
    long size  = ftell(fp);
    fclose(fp);

    return (int)(size / (long)sizeof(DiaryEntry));
}

/* Next available ID = total record count + 1 */
int getNextId(void) {
    return getEntryCount() + 1;
}