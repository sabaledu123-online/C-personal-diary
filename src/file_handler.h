#pragma once

#include "diary.h"
#include "utils.h"
#include<stdio.h>
/* ─── File Operations ────────────────────────────────────────── */

/* Reads all records from DATA_FILE into entries[], returns count */
int  loadAllEntries(DiaryEntry entries[], int max);

/* Appends a single DiaryEntry to the end of DATA_FILE */
void saveNewEntry(const DiaryEntry *entry);

/* Overwrites the record at position (id - 1) in DATA_FILE */
void updateEntryById(const DiaryEntry *entry);

/* Returns total number of records in DATA_FILE (including deleted) */
int  getEntryCount(void);

/* Returns the next available ID (getEntryCount + 1) */
int  getNextId(void);

