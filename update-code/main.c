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

void cmpLine(FILE *, FILE *);

int main(int argc, char *argv[]) {
    if(argc != ARGC_PARAMETERS) errorHandler(ERROR_ARGC);

    FILE *lastFile, *newFile, *output;
    if((lastFile = fopenList(argv[ARGV_FILE], "r")) == NULL) errorHandler(ERROR_FILE);
    if((newFile = fopenList(argv[ARGV_NEW_FILE], "r")) == NULL) errorHandler(ERROR_FILE);
    if((output = fopenList(argv[ARGV_OUTPUT], "w")) == NULL) errorHandler(ERROR_FILE);

    cmpLine(lastFile, newFile);

    return 0;
}

void cmpLine(FILE *lastFile, FILE *newFile) {
    size_t length = LINE_LENGTH;
    char *line1, *line2;

    if((line1 = (char *)mallist(LINE_LENGTH + 1)) == NULL) errorHandler(ERROR_MEMORY);
    if((line2 = (char *)mallist(LINE_LENGTH + 1)) == NULL) errorHandler(ERROR_MEMORY);

    getline(&line1, &length, lastFile);
    getline(&line2, &length, newFile);

    if(!strcmp(line1, line2)) printf("Igualito.\n");
    else printf("Distinto manito.\n");
}