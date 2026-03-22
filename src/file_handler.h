#pragma once

#include "diary.h"
#include "utils.h"
#include <stdio.h>

// -- File operations --

// Reads records from data file and loads the diary entries.
int loadAllEntries(DiaryEntry entries[], int max);

// Appends a single data entry to data file.
void saveNewEntry(const DiaryEntry *entry);

/*
    Overwrites a single record in-place using fseek.
    Offset = (id - 1) * sizeof(DiaryEntry)
    offset sets the file pointer to that exact entry's location
    then overwrites exactly that entry as size matches exactly.
*/
void updateEntryById(const DiaryEntry *entry);

/*
    Returns the current entry count by utilizing the sizeof() operator .
    filesize/singleEntrySize = entry count.
    counts soft deleted ones (Deactivated ones)
    as they to contribute to the overall filesize.
*/
int getEntryCount(void);

// Returns the next available ID: getEntryCount() +1;
int getNextId(void);
