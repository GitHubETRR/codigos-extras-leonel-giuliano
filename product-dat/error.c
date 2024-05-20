#include <stdio.h>
#include <stdlib.h>

#include "error.h"

void errorHandler(errorEvent_t error) {
    printf("ERROR: ");

    switch(error) {
        case ERROR_ARGC:
            puts("Usage: main.exe (file.dat)[OPTIONAL].");
            break;

        case ERROR_FILE:
            puts("There was a problem with the file.");
            break;

        case ERROR_MEMORY:
            puts("There was a problem allocating.");
            break;

        case ERROR_FILEREMOVE:
            puts("The file couldn't been remove.");
            break;

        default:
            puts("Unkown error.");
            break;
    }

    exit(EXIT_FAILURE);
}