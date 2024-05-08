#include <stdio.h>

#define ARGC_AMOUNT 3
#define RESULT "../result.txt"

enum {
    ARGV_PROGRAM,
    ARGV_TEXT1,
    ARGV_TEXT2
};

void createFilePointers(FILE **pText1, FILE **pText2, FILE **pResult, char *argv[]);
void checkCh(FILE *pText1, FILE *pText2);
void compareStr(FILE *pText1, FILE *pText2, char ch);