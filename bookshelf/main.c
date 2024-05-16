#include <stdio.h>

#include "main.h"
#include "file.h"
#include "error.h"

int main(int argc, char *argv[]) {
    if(argc != ARGC_PARAMETERS) errorHandler(ERROR_ARGC);

    FILE *spreadsheet;
    if((spreadsheet = fopen(argv[ARGV_OUTPUT], "a+")) == NULL)
        errorHandler(ERROR_FILE);
    // Open file in append mode to read past data

    uint8_t exitPrevent = 0;
    menuState_t menuState;
    do {
        menu(&menuState, &spreadsheet, argv);
        exitPrevent++;
    }while(menuState != MENU_END && exitPrevent != MAINLOOP_LIMIT);
    // Loops the menu until it's finished or an error happens

    delList();
    fclose(spreadsheet);

    return 0;
}

void menu(menuState_t *menuState, FILE **spreadsheet, char *argv[]) {
    void (*menuF[])(FILE **, char *[]) = {
        menuAdd,
        menuPrintEntries,
        menuDelEntry
    };
    // Pointer with every option in the menu

    printf("%u. Enter a new entry.\n", ADD_ENTRY);
    printf("%u. Print the new entries from last to first.\n", PRINT_NEW_ENTRIES);
    printf("%u. Delete an entry.\n", DELETE_ENTRY);
    printf("%u. Erase all the entries from the list.\n", DELETE_LIST);
    printf("%u. Exit the program.\n\n", MENU_END);

    printf("Choose you option: ");
    scanf("%u", menuState);
    printf("\n");

    if(*menuState > MENU_START && *menuState <= MENU_END)
        menuF[*menuState - 1](spreadsheet, argv);
        
    else printf("Select a given option.\n");
    // Acts as a switch

    printf("\n++++++++++++++++++++\n\n");
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

void menuAdd(FILE **spreadsheet, char *argv[]) {
    newEntry(spreadsheet);
}

void menuPrintEntries(FILE **spreadsheet, char *argv[]) {
    printEntries();
}

void menuDelEntry(FILE **spreadsheet, char *argv[]) {
    if(choice("Do you really meant to delete an entry?")) {
        char user[NAME_LENGTH];
        size_t bookNum;

        printf("\nEnter the user name: ");
        scanf(" %[^\n]", user);
        printf("Enter the book number: ");
        scanf(" %u", &bookNum);

        readData(spreadsheet);
        delEntry(user, bookNum, spreadsheet);
    } else printf("Returning to the menu...\n");
}