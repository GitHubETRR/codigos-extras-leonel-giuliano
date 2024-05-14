#include "list.h"
#include "error.h"

static spreadsheet_t *list = NULL;

void readData(FILE *spreadsheet) {
    static size_t exitPrevent = 1;
    // Num in case the recursion exceeds EXIT_PREVENT

    spreadsheet_t *book = (spreadsheet_t *)malloc(sizeof(spreadsheet_t));
    if(book == NULL) errorHandler(ERROR_MEMORY);
    // Create a new book that will contain the data from the text

    fseek(spreadsheet, SPREAD_I, SEEK_CUR);
    fscanf(spreadsheet, "%d", &(book->i));
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
    // Sets the - spaces for the following iteration

    free(book);
    exitPrevent++;
    if(!feof(spreadsheet) && exitPrevent != EXIT_PREVENT) readData(spreadsheet);
    // Recursion until the file finishes

    printf("%s\n", list->user);

    fflush(spreadsheet);
}