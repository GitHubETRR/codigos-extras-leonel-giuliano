#include <stdio.h>

#include "list.h"

void readData(FILE *);                      /* Reads all the books from the list */
void uploadData(FILE **, spreadsheet_t *);  /* Uploads the new book */
void delSheet(FILE **, char *[]);           /* Empties the whole file */