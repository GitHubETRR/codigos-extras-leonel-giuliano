#include <stdio.h>

#include "list.h"

// Amounts of bytes from a point to another
#define CHAR_USER 6             /* "User: " */
#define CHAR_BOOK_NUM 8         /* "Book N\u00B0" */

// Amounts of '\n'
#define LINE_I_USER 1           /* From number to user */
#define LINE_USER_BOOK_NUM 2    /* From user to book num */
#define LINE_USER_END 7         /* From user to the end */
#define LINE_BOOK_NUM_END 4     /* From book num to the end */

enum {
    POS_A,
    POS_B,
    POS_AMOUNT
};
// Positions when is searching for an entry

void uploadData(spreadsheet_t *, FILE **);          /* Uploads the new book */
void searchEntry(const char *, size_t, FILE **);    /* Searchs for the entry */
void delSheet(char *[], FILE **);                   /* Empties the whole file */