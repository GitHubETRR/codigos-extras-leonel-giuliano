#include <stdio.h>
#include <stdlib.h>

#include "error.h"

void errorHandler(errorEvent_t error) {
    printf("ERROR: ");

    switch(error) {
        case ERROR_ARGC:
            printf("Usage: main.exe [last-code] [new-code] [output.txt].\n");
            break;

        case ERROR_FILE:
            printf("There was a problem with the file.\n");
            break;

        case ERROR_MEMORY:
            printf("There was a problem with the allocation.\n");
            break;

        default:
            printf("Unkown error.\n");
            break;
    }

    exit(EXIT_FAILURE);
}