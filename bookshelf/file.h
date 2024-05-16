#include <stdio.h>

#include "list.h"

// Amount of char between points
#define CH_I 3
#define CH_USER 8
#define CH_TITLE 9
#define CH_BOOK_NUM 10
#define CH_INIT_DAY 15
#define CH_FINAL_DAY 14
#define CH_SLASH 24

void uploadData(spreadsheet_t *, FILE **);  /* Uploads the new book */
void readData(FILE **);                     /* Reads all the entries from the file */
void delSheet(FILE **, char *[]);           /* Empties the whole file */