#include <stdio.h>

#include "file.h"

int main(int argc, char *argv[]) {
    if(argc != ARGC_LENGHT) {
        printf("Usage: main.exe [text-1] [text-2].\n");

        return 1;
    }

    FILE *pText1, *pText2, *pResult;
    // Gives the pointers the position of the file
    configFiles(&pText1, &pText2, &pResult, argv);

    fclose(pText1);
    fclose(pText2);
    fclose(pResult);

    return 0;
}