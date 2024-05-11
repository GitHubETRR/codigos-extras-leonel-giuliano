#include <stdio.h>

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

    return 0;
}