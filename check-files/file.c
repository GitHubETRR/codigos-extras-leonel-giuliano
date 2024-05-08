#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"

void configFiles(FILE **pText1, FILE **pText2, FILE **pResult, char *argv[]) {
    *pText1 = fopen(argv[ARGV_TEXT1], "r");
    if(pText1 == NULL) {
        printf("The file '%s' couldn't been open.\n", argv[ARGV_TEXT1]);

        exit(1);
    }

    *pText2 = fopen(argv[ARGV_TEXT2], "r");
    if(pText2 == NULL) {
        printf("The file '%s' couldn't been open.\n", argv[ARGV_TEXT2]);

        exit(1);
    }

    // Returns the strings concatenated
    char *outputResult = concat(OUTPUT_FOLDER, RESULT);
    *pResult = fopen(outputResult, "w");
    if(pResult == NULL) {
        printf("There was a problem creating '%s'.\n", RESULT);
        free(outputResult);

        exit(1);
    }

    free(outputResult);
}

// Concatenates 2 strings. The result needs to be free
char *concat(const char *str1, const char *str2) {
    size_t str1Lenght = strlen(str1);
    size_t str2Lenght = strlen(str2);
    // Needed to know the size of the result
    char *result;

    if((result = malloc(str1Lenght + str2Lenght + 1)) == NULL) {    /* '+1' for null */
        printf("There is no memory left.\n");

        exit(1);
    }

    strcat(result, str1);
    strcat(result, str2);

    return result;
}