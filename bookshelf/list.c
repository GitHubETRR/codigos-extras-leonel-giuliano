#include <stdlib.h>
#include <string.h>

#include "file.h"
#include "error.h"

spreadsheet_t *list = NULL;

void newEntry(FILE **spreadsheet) {
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

    uploadData(book, spreadsheet);
    // Saves the entry inside the spreadsheet

    book->next = list;
    list = book;
    // Adds the entry to the list
}

void printEntries(FILE **spreadsheet) {
    uint16_t exitPrevent = 0;
    spreadsheet_t *iEntry = list;

    while(iEntry != NULL && exitPrevent != LISTLOOP_LIMIT) {
        printf("N%c%d\n", GRADE_ASCII, iEntry->i);
        printf("User: %s\n", iEntry->user);
        printf("Title: %s\n", iEntry->title);
        printf("Book N%c%d\n", GRADE_ASCII, iEntry->bookNum);
        printf("Initial day: %s\n", iEntry->initDate);
        printf("Return day: %s\n", iEntry->finalDate);
        printf("--------------------\n");
        // Prints all the data from the entry

        iEntry = iEntry->next;
        // Moves to the next entry on the list
    }

    if(list == NULL) printf("There are no entries.\n");
}

void delEntry(const char *user, size_t bookNum) {
    uint16_t exitPrevent = 0;
    spreadsheet_t *beforeEntry = NULL, *delEntry = list;
    // beforeEntry tracks the entry from before
    // delEntry is every entry from the list

    while(delEntry != NULL && exitPrevent != LISTLOOP_LIMIT) {
        if(!strcmp(user, delEntry->user) && bookNum == delEntry->bookNum) {
            if(list->next != NULL) beforeEntry->next = delEntry->next;
            // Detaches the entry from the list

            free(delEntry);
            break;
        }
        // Checks for the user and the book num

        beforeEntry = delEntry;
        delEntry = delEntry->next;
        // Tries with the next entry
    }
}

void delList() {
    uint16_t exitPrevent = 0;
    spreadsheet_t *delBook;

    while(list != NULL && exitPrevent != LISTLOOP_LIMIT) {
        delBook = list;
        list = list->next;
        // Detaches the last element from the list

        free(delBook);

        exitPrevent++;
    }
}