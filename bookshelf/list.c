#include "list.h"
#include "error.h"

static spreadsheet_t *list = NULL;

void readData(FILE *spreadsheet) {
    size_t exitPrevent = 1;
    // Num in case the loop exceeds EXIT_PREVENT

    spreadsheet_t *book = (spreadsheet_t *)malloc(sizeof(spreadsheet_t));
    if(book == NULL) {
        free(list);
        fclose(spreadsheet);

        errorHandler(ERROR_MEMORY);
    }
    // Create a new book that will contain the data from the text

    while(!feof(spreadsheet) && exitPrevent != EXIT_PREVENT) {
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

        exitPrevent++;
        // Prevents a large while
    }

    free(book);

    fflush(spreadsheet);
}

void uploadData(FILE **spreadsheet, spreadsheet_t *book) {
    fprintf(*spreadsheet, "N%c%d\n", GRADE, book->i);
    fprintf(*spreadsheet, "User:%c%s\n", NBSP, book->user);
    fprintf(*spreadsheet, "Title: #%s\n", book->title);
    fprintf(*spreadsheet, "Book N%c%d\n", GRADE, book->bookNum);
    fprintf(*spreadsheet, "Initial day: %s\n", book->initDate);
    fprintf(*spreadsheet, "Return day: %s\n", book->finalDate);
    // Prints all the new items inside the file

    fputs("--------------------\n", *spreadsheet);
    fflush(*spreadsheet);
}

void newBook(FILE **spreadsheet) {
    spreadsheet_t *book = (spreadsheet_t *)malloc(sizeof(spreadsheet_t));
    if(book == NULL) {
        free(list);
        fclose(spreadsheet);

        exit(ERROR_MEMORY);
    }

    uint16_t lastI = (list == NULL) ? 0 : list->i;
    // Makes the lastI be equal to the one from the list
    // In case the list is empty, it sets it to 0
    book->i = lastI + 1;

    printf("User: ");
    scanf("%[^\n]", book->user);
    printf("Title: ");
    scanf("%[^\n]", book->title);
    printf("Number of the book: ");
    scanf("%u", &(book->bookNum));
    printf("Initial day: ");
    scanf("%[^\n]", book->initDate);
    printf("Return day: ");
    scanf("%[^\n]", book->finalDate);

    uploadData(spreadsheet, book);

    free(book);
}