#define _POSIX_C_SOURCE 200809L
// Enables the function getline()

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "error.h"
#include "mallist.h"

#define ARGC_PARAMETERS 4
enum {
    ARGV_PATH,
    ARGV_FILE,
    ARGV_NEW_FILE,
    ARGV_OUTPUT
};
// Index of the argv values

#define LINE_LENGTH 150     /* Max lenght for getline() */

void cmpLine(FILE *, FILE *, FILE **);      /* Compares if the lines are equal */

int main(int argc, char *argv[]) {
    if(argc != ARGC_PARAMETERS) errorHandler(ERROR_ARGC);
    // Error in case the user didn't pass the needed parameters

    FILE *lastFile, *newFile, *output;
    if((lastFile = fopenList(argv[ARGV_FILE], "r")) == NULL) errorHandler(ERROR_FILE);
    if((newFile = fopenList(argv[ARGV_NEW_FILE], "r")) == NULL) errorHandler(ERROR_FILE);
    if((output = fopenList(argv[ARGV_OUTPUT], "w")) == NULL) errorHandler(ERROR_FILE);

    while(!feof(lastFile) && !feof(newFile)) cmpLine(lastFile, newFile, &output);

    // freeAll();
    fcloseAll();

    return 0;
}

void cmpLine(FILE *lastFile, FILE *newFile, FILE **output) {
    static size_t i = 1;
    size_t length = LINE_LENGTH;
    // Pass it to a size_t for the getline()
    char *line1, *line2;        /* Lines from the files */

    if((line1 = (char *)mallist(LINE_LENGTH + 1)) == NULL) errorHandler(ERROR_MEMORY);
    if((line2 = (char *)mallist(LINE_LENGTH + 1)) == NULL) errorHandler(ERROR_MEMORY);

    getline(&line1, &length, lastFile);
    getline(&line2, &length, newFile);

    if(strcmp(line1, line2)) {
        fprintf(*output, "     -----   DIFFERENCE IN LINE %d   -----\n", i);
        fprintf(*output, "old file: %s", line1);
        fprintf(*output, "new file: %s\n", line2);

        fflush(*output);
    }

    i++;

    freePtr(line1);
    freePtr(line2);
}