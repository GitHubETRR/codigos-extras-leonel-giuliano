#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// spreadsheet_t
#define DATE_LENGTH 8       /* mm/dd/yy */
#define NAME_LENGTH 50

// Amount of char from a point to another inside spreadsheet
#define SPREAD_I 2          /* "N°" */
#define SPREAD_USER 7       /* "\nUser: " */
#define SPREAD_TITLE 9      /* "\nTitle: #" */
#define SPREAD_BOOK 8       /* "\nBook N°" */
#define SPREAD_INIT 14      /* "\nInitial day: " */
#define SPREAD_FINAL 13     /* "\nReturn day: " */
#define SPREAD_SPACE 22     /* "\n--------------------\n" */

// Extended chars
#define GRADE 248       /* ° */
#define NBSP 255        /*   */

typedef struct _book {
    uint16_t i;

    char user[NAME_LENGTH];
    char title[NAME_LENGTH];

    size_t bookNum;

    char initDate[DATE_LENGTH];
    char finalDate[DATE_LENGTH];

    struct _book *next;
}spreadsheet_t;

// LIST FUNCTIONS
void newBook(FILE **);



// FILE FUNCTIONS
void readData(FILE *);
void uploadData(FILE **, spreadsheet_t *);