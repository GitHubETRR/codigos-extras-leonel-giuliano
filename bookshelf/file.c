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

void searchEntry(const char *user, size_t bookNum, FILE **spreadsheet) {
    ENTRY_FOUND = 0;
    uint8_t exitPrevent = 0;
    char ch = ' ', fileUser[NAME_LENGTH];
    size_t fileBookNum;

    fseek(*spreadsheet, 0, SEEK_END);
    size_t pos[POS_AMOUNT] = {0}, fileLength = ftell(*spreadsheet);
    // posA saves the initial position of the entry
    // posB saves the final position of the entry
    rewind(*spreadsheet);

    printf("%u\n", fileLength);

    while(fileLength - pos[POS_B] && !ENTRY_FOUND && exitPrevent != 20) {
        uint8_t nLimit = LINE_I_USER, nAmount = 0;
        // nAmounts is the amount of '\n' passed
        // nLimit is the amount of '\n' wanted

        pos[POS_A] = ftell(*spreadsheet);
        // Get the initial position

        while(ch != '\n' && nAmount != nLimit) {
            ch = fgetc(*spreadsheet);

            if(ch == '\n') nAmount++;
        }
        // Searches for the user

        nAmount = 0;
        nLimit = LINE_USER_END;

        fseek(*spreadsheet, CHAR_USER, SEEK_CUR);
        fscanf(*spreadsheet, "%[^\n]", fileUser);
        // Scans the user

        if(!strcmp(user, fileUser)) {       /* Looks if they are the same */
            while(nAmount != LINE_USER_BOOK_NUM && ch != EOF) {
                ch = fgetc(*spreadsheet);

                if(ch == '\n') nAmount++;
            }
            // Searches for the book number

            fseek(*spreadsheet, CHAR_BOOK_NUM, SEEK_CUR);
            fscanf(*spreadsheet, "%u", &fileBookNum);
            // Scans the book number

            if(bookNum == fileBookNum) ENTRY_FOUND = 1;
            else nLimit = LINE_BOOK_NUM_END;

            nAmount = 0;
        }

        while(nAmount != nLimit && ch != EOF) {
            ch = fgetc(*spreadsheet);

            if(ch == '\n') nAmount++;
        }
        // Searches for the end of the entry

        pos[POS_B] = ftell(*spreadsheet);

        exitPrevent++;
    }

}

void delSheet(char *argv[], FILE **spreadsheet) {
    (*spreadsheet) = freopen(argv[ARGV_OUTPUT], "w+", *spreadsheet);
    // Empties the file by reopening it
}