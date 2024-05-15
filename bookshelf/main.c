#include <stdio.h>

#include "main.h"
#include "list.h"
#include "error.h"

int main(int argc, char *argv[]) {
    if(argc != ARGC_PARAMETERS) errorHandler(ERROR_ARGC);

    FILE *spreadsheet;
    if((spreadsheet = fopen(argv[ARGV_OUTPUT], "a+")) == NULL) errorHandler(ERROR_FILE);
    // Opens in append in case there was data saved

    readData(spreadsheet);
    newBook(&spreadsheet);

    delList();
    fclose(spreadsheet);

    return 0;
}