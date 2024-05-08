#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"

void createFilePointers(FILE **pText1, FILE **pText2, FILE **pResult, char *argv[]) {
    *pText1 = fopen(argv[ARGV_TEXT1], "r");
    *pText2 = fopen(argv[ARGV_TEXT2], "r");

    if(pText1 == NULL || pText2 == NULL) {
        printf(
            "The files '%s' or '%s' couldn't been open.\n",
            argv[ARGV_TEXT1],
            argv[ARGV_TEXT2]
        );

        exit(1);
    }

    *pResult = fopen(RESULT, "w");

    if(pResult == NULL) {
        printf("There was a problem creating '%s'.\n", RESULT);

        exit(1);
    }
}

void checkCh(FILE *pText1, FILE *pText2) {
    rewind(pText1);
    char ch;

    while((ch = fgetc(pText1)) != EOF) {
        if(ch != ' ' || ch != '\n') compareStr(pText1, pText2, ch);
    }

    printf("Finiquitaditisimo brother.\n");
}

void compareStr(FILE *pText1, FILE *pText2, char ch) {
    char *str1;
    size_t position = ftell(pText1), strLenght = 0;

    do strLenght++;
    while((ch = fgetc(pText1)) != EOF || ch != ' ' || ch != '\n');

    fseek(pText1, position, SEEK_SET); 
    fseek(pText2, position, SEEK_SET); 

    exit(1);    /*  */

    if((str1 = malloc(strLenght * sizeof(char))) == NULL) {
        printf("There is no memory left.\n");

        exit(1);
    }file

    fclose(pText2); /*  */
    exit(1);
}