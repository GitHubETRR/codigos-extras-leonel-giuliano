#include <stdio.h>
#include <stdint.h>

// spreadsheet_t
#define DATE_LENGTH 9       /* mm/dd/yy */
#define NAME_LENGTH 51

// Extended chars
#define GRADE "\u00B0"      /* ° */
#define GRADE_ASCII 248     /* ° */

typedef struct _book {
    uint16_t i;

    char user[NAME_LENGTH];
    char title[NAME_LENGTH];

    size_t bookNum;

    char initDate[DATE_LENGTH];
    char finalDate[DATE_LENGTH];

    struct _book *next;
}spreadsheet_t;

void newEntry(FILE **);                 /* Adds a new book to the list */
void printEntries(FILE **);             /* Prints all the new entries */
void delEntry(const char *, size_t);    /* Deletes an entry */
void delList(void);                     /* Deletes all the elements inside the list */

extern spreadsheet_t *list;
// Extern the list to use it inside 'file.c'