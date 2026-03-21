# Diary — A Terminal-Based Journal in C

A command-line diary application written in C. Entries are stored locally
in a binary file. The project was built to practice structured C programming,
file I/O, and clean module design.

---

## Features

- Add, view, edit, and soft-delete diary entries
- Search entries by date, ID, or keyword
- Persistent binary storage with in-place record updates
- Input validation and buffer-safe reading

---

## Project Structure

diary/<br>
     ├── main.c<br>
├── diary.c / diary.h         — core entry operations<br>
├── file_handler.c / .h       — binary file read/write<br>
├── menu.c / menu.h           — CLI menu and dispatch<br>
├── utils.c / utils.h         — input handling, formatting, validation<br>
└── data/<br>
............... └── diary.dat             — generated at runtime

---

## Build

Requires GCC or any C99-compatible compiler.

    gcc main.c diary.c file_handler.c menu.c utils.c -o diary

Or with the Makefile:

    make

---

## Run

    ./diary

On Windows:

    diary.exe

---

## Usage

The application presents a menu on launch.

    [1]  Add Entry
    [2]  View All Entries
    [3]  Search Entries
    [4]  Edit / Update Entry
    [5]  Delete Entry
    [0]  Exit

Entries are stored in data/diary.dat. This file is created automatically
on first run. Deleted entries are soft-deleted — they remain in the file
but are excluded from all views and searches.

---

## Technical Notes

- Storage: fixed-size binary records using fwrite / fread
- Updates: in-place overwrites via fseek, offset = (id - 1) * sizeof(DiaryEntry)
- IDs: strictly sequential and 1-based; do not manually edit the .dat file
- Soft delete: is_deleted flag per record, never physically removed

---

## Limitations

- Maximum of 30 entries (defined by MAX_ENTRIES in diary.h)
- Single-line content input only
- No encryption or access control

---

## Author

`... Alfred ...`
