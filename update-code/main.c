#include <stdio.h>
#include <stdint.h>

#include "error.h"
#include "mallist.h"

#define ARGC_PARAMETERS 4

enum {
    ARGV_PATH,
    ARGV_FILE,
    ARGV_NEW_FILE,
    ARGV_OUTPUT
};

int main(int argc, char *argv[]) {
    if(argc != ARGC_PARAMETERS) errorHandler(ERROR_ARGC);

    FILE *lastFile, *newFile, *output;
    if((lastFile = fopenList(argv[ARGV_FILE], "r")) == NULL) errorHandler(ERROR_FILE);
    if((newFile = fopenList(argv[ARGV_NEW_FILE], "r")) == NULL) errorHandler(ERROR_FILE);
    if((output = fopenList(argv[ARGV_OUTPUT], "w")) == NULL) errorHandler(ERROR_FILE);

    return 0;
}