#include <stdlib.h>

#include "file.h"
#include "main.h"
#include "error.h"

void uploadData(spreadsheet_t *book, FILE **spreadsheet) {
    fprintf(*spreadsheet, "N%s%d\n", GRADE, book->i);
    fprintf(*spreadsheet, "User: %s\n", book->user);
    fprintf(*spreadsheet, "Title: %s\n", book->title);
    fprintf(*spreadsheet, "Book N%s%d\n", GRADE, book->bookNum);
    fprintf(*spreadsheet, "Initial day: %s\n", book->initDate);
    fprintf(*spreadsheet, "Return day: %s\n", book->finalDate);
    // Prints all the new items inside the file

    fputs("--------------------\n", *spreadsheet);
    fflush(*spreadsheet);
}

void delSheet(char *argv[], FILE **spreadsheet) {
    (*spreadsheet) = freopen(argv[ARGV_OUTPUT], "w+", *spreadsheet);
    // Empties the file by reopening it
}