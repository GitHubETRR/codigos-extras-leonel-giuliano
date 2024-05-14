#include <stdio.h>
#include <stdlib.h>

// spreadsheet_t
#define DATE_LENGTH 8       /* mm/dd/yy */
#define NAME_LENGTH 50

// Amount of char from a point to another inside spreadsheet
#define SPREAD_I 2          /* N° */
#define SPREAD_USER 8       /* \nUser: $ */
#define SPREAD_TITLE 9      /* \nTitle: # */
#define SPREAD_BOOK 8       /* \nBook N° */
#define SPREAD_INIT 14      /* \nInitial day:  */
#define SPREAD_FINAL 13     /* \nReturn day:  */
#define SPREAD_SPACE 22     /* \n--------------------\n */

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