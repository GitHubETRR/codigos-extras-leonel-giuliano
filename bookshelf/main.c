#include <stdio.h>

#include "main.h"
#include "file.h"
#include "error.h"

int main(int argc, char *argv[]) {
    if(argc != ARGC_PARAMETERS) errorHandler(ERROR_ARGC);

    FILE *spreadsheet;
    if((spreadsheet = fopen(argv[ARGV_OUTPUT], "a+")) == NULL) errorHandler(ERROR_FILE);
    // Opens in append in case there was data saved

    uint16_t exitPrevent = 0;
    menuState_t menuState;
    do {
        menu(&menuState, &spreadsheet);
        exitPrevent++;
    }while(menuState != END && exitPrevent != EXIT_PREVENT);
    // Loops the menu until it's finished or an error happens

    delList();
    fclose(spreadsheet);

    return 0;
}

void menu(menuState_t *menuState, FILE **spreadsheet) {
    printf("%u. Enter a new entry.\n", ADD_ENTRY);
    printf("%u. Print the spreadsheet.\n", PRINT_SPREADSHEET);
    printf("%u. Delete an entry.\n", DELETE_ENTRY);
    printf("%u. ", DELETE_LIST);
}

uint8_t choice(const char *msg) {
    uint8_t bool = 0;
    char option;

    printf("%s\t[y/n]: ", msg);
    scanf(" %c", &option);
    // Scan the option given by the user

    if(option == 'y' || option == 'Y') bool = 1;
    
    return bool;
    // Retuns 1 if yes, returns 0 in every other case
}