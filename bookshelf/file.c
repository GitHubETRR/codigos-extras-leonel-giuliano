#include <stdlib.h>
#include <string.h>

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

void readData(FILE **spreadsheet) {
    delList();
    // Deletes the whole list to read the file instead
    
    uint16_t exitPrevent = 0;
    fseek(*spreadsheet, 0, SEEK_END);
    size_t pos = 0, fileLength = ftell(*spreadsheet);
    rewind(*spreadsheet);
    // Compares the actual position with the end

    while(fileLength - pos && exitPrevent != LISTLOOP_LIMIT) {
        spreadsheet_t *newBook;
        if((newBook = (spreadsheet_t *)malloc(sizeof(spreadsheet_t))) == NULL) {
            fclose(*spreadsheet);

            errorHandler(ERROR_MEMORY);
        }

        fseek(*spreadsheet, CH_I, SEEK_CUR);
        fscanf(*spreadsheet, "%u", &(newBook->i));
        fseek(*spreadsheet, CH_USER, SEEK_CUR);
        fscanf(*spreadsheet, "%[^\n]", newBook->user);
        fseek(*spreadsheet, CH_TITLE, SEEK_CUR);
        fscanf(*spreadsheet, "%[^\n]", newBook->title);
        fseek(*spreadsheet, CH_BOOK_NUM, SEEK_CUR);
        fscanf(*spreadsheet, "%u", &(newBook->bookNum));
        fseek(*spreadsheet, CH_INIT_DAY, SEEK_CUR);
        fscanf(*spreadsheet, "%[^\n]", newBook->initDate);
        fseek(*spreadsheet, CH_FINAL_DAY, SEEK_CUR);
        fscanf(*spreadsheet, "%[^\n]", newBook->finalDate);
        fseek(*spreadsheet, CH_SLASH, SEEK_CUR);
        // Scan all the data from an entry

        pos = ftell(*spreadsheet);

        newBook->next = list;
        list = newBook;

        exitPrevent++;
    }
    // Scans through the whole file
}

void delSheet(FILE **spreadsheet, char *argv[]) {
    (*spreadsheet) = freopen(argv[ARGV_OUTPUT], "w+", *spreadsheet);
    // Empties the file by reopening it
}