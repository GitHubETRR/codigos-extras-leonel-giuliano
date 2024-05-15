#include <stdlib.h>

#include "file.h"
#include "main.h"
#include "error.h"

void readData(FILE *spreadsheet) {
    uint16_t exitPrevent = 1;
    // Num in case the loop exceeds EXIT_PREVENT

    fseek(spreadsheet, 0, SEEK_END);
    size_t pos = 0, fileLength = ftell(spreadsheet);
    rewind(spreadsheet);
    // Gets the value that pos has to offer when
    // the file is at it's end point

    while(fileLength - pos && exitPrevent != EXIT_PREVENT) {
        spreadsheet_t *book = (spreadsheet_t *)malloc(sizeof(spreadsheet_t));
        if(book == NULL) {
            delList();
            fclose(spreadsheet);

            errorHandler(ERROR_MEMORY);
        }
        // Create a new book that will contain the data from the text
        
        fseek(spreadsheet, SPREAD_I, SEEK_CUR);
        fscanf(spreadsheet, "%hu", &(book->i));
        // Scan the number

        fseek(spreadsheet, SPREAD_USER, SEEK_CUR);
        fscanf(spreadsheet, "%[^\n]", book->user);
        // Scan the name of the user

        fseek(spreadsheet, SPREAD_TITLE, SEEK_CUR);
        fscanf(spreadsheet, "%[^\n]", book->title);
        // Scan the title

        fseek(spreadsheet, SPREAD_BOOK, SEEK_CUR);
        fscanf(spreadsheet, "%u", &(book->bookNum));
        // Scan the number of the book

        fseek(spreadsheet, SPREAD_INIT, SEEK_CUR);
        fscanf(spreadsheet, "%[^\n]", book->initDate);
        // Scan the date when the book was taken

        fseek(spreadsheet, SPREAD_FINAL, SEEK_CUR);
        fscanf(spreadsheet, "%[^\n]", book->finalDate);
        // Scan the date when the book has to be returned

        book->next = list;
        list = book;
        // Connects the book with the entire list

        fseek(spreadsheet, SPREAD_SPACE, SEEK_CUR);
        pos = ftell(spreadsheet);
        // Sets the - spaces for the following iteration
        // Tells the position of the seek in case it finished

        exitPrevent++;
        // Prevents a large while
    }
}

void uploadData(FILE **spreadsheet, spreadsheet_t *book) {
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

void delSheet(FILE **spreadsheet, char *argv[]) {
    (*spreadsheet) = freopen(argv[ARGV_OUTPUT], "w+", *spreadsheet);
    // Empties the file by reopen it
}