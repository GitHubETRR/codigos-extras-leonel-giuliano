#include <stdio.h>

#include "main.h"
#include "file.h"
#include "error.h"

int main(int argc, char *argv[]) {
    if(argc != ARGC_PARAMETERS) errorHandler(ERROR_ARGC);

    FILE *spreadsheet;
    if((spreadsheet = fopen(argv[ARGV_OUTPUT], "a+")) == NULL) errorHandler(ERROR_FILE);
    // Opens in append in case there was data saved

    readData(spreadsheet);
    newBook(&spreadsheet);

    if(choice("Do you want to delete the file?")) delSheet(&spreadsheet, argv);

    delList();
    fclose(spreadsheet);

    return 0;
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