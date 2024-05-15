#include "file.h"
#include "error.h"

spreadsheet_t *list = NULL;

void newBook(FILE **spreadsheet) {
    spreadsheet_t *book = (spreadsheet_t *)malloc(sizeof(spreadsheet_t));
    if(book == NULL) {
        delList();
        fclose(*spreadsheet);

        exit(ERROR_MEMORY);
    }

    uint16_t lastI = (list == NULL) ? 0 : list->i;
    // Makes the lastI be equal to the one from the list
    // In case the list is empty, it sets it to 0
    book->i = lastI + 1;

    printf("User: ");
    scanf(" %[^\n]", book->user);
    printf("Title: ");
    scanf(" %[^\n]", book->title);
    printf("Number of the book: ");
    scanf(" %u", &(book->bookNum));
    printf("Initial day: ");
    scanf(" %s", book->initDate);
    printf("Return day: ");
    scanf(" %s", book->finalDate);

    uploadData(spreadsheet, book);
}

void delList() {
    uint16_t exitPrevent = 1;
    spreadsheet_t *delBook;

    while(list != NULL && exitPrevent != EXIT_PREVENT) {
        delBook = list;
        list = list->next;
        // Detaches the last element from the list

        free(delBook);

        exitPrevent++;
    }
}