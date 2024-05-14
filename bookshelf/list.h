#include <stdio.h>
#include <stdlib.h>

// spreadsheet_t
#define DATE_LENGTH 8       /* mm/dd/yy */
#define NAME_LENGTH 50

// Amount of char from a point to another inside spreadsheet
#define SPREAD_I 2
#define SPREAD_USER 7
#define SPREAD_TITLE 7
#define SPREAD_BOOK 7
#define SPREAD_INIT 13
#define SPREAD_FINAL 12
#define SPREAD_SPACE 20

typedef struct _book {
    size_t i;

    char user[NAME_LENGTH];
    char title[NAME_LENGTH];

    size_t bookNum;

    char initDate[DATE_LENGTH];
    char finalDate[DATE_LENGTH];

    struct _book *next;
}spreadsheet_t;

void readData(FILE *);