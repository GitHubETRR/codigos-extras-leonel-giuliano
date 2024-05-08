#include <stdio.h>

#include "file.h"

int main(int argc, char *argv[]) {
    if(argc != ARGC_AMOUNT) {
        printf("Usage: main.exe [text1] [text2].\n");

        return 1;
    }

    FILE *pText1, *pText2, *pResult;
    createFilePointers(&pText1, &pText2, &pResult, argv);

    checkCh(pText1, pText2);

    fclose(pText1);
    fclose(pText2);
    fclose(pResult);
}