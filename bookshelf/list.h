#include <stdio.h>
#include <stdint.h>

// spreadsheet_t
#define DATE_LENGTH 9       /* mm/dd/yy */
#define NAME_LENGTH 51

// Amount of char from a point to another inside spreadsheet
// Every multichar counts as 2 positions
// '\n' counts as 1
#define SPREAD_I 3          /* "N\u00B0" */
#define SPREAD_USER 8       /* "\nUser: " */
#define SPREAD_TITLE 9      /* "\nTitle: " */
#define SPREAD_BOOK 10       /* "\nBook N\u00B0" */
#define SPREAD_INIT 15      /* "\nInitial day: " */
#define SPREAD_FINAL 14     /* "\nReturn day: " */
#define SPREAD_SPACE 24     /* "\n--------------------\n" */

// Extended chars
#define GRADE "\u00B0"      /* ° */

typedef struct _book {
    uint16_t i;

    char user[NAME_LENGTH];
    char title[NAME_LENGTH];

    size_t bookNum;

    char initDate[DATE_LENGTH];
    char finalDate[DATE_LENGTH];

    struct _book *next;
}spreadsheet_t;

void newBook(FILE **);      /* Adds a new book to the list */
void delList(void);         /* Deletes all the elements inside the list */

extern spreadsheet_t *list;
// Extern the list to use it inside 'file.c'