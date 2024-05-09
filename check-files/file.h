#include <stdio.h>

#define ARGC_LENGHT 3       /* Parameters when called 'main.exe' */
enum {      /* Every parameter when called 'main.exe' */
    ARGV_PROGRAM,
    ARGV_TEXT1,
    ARGV_TEXT2
};

#define OUTPUT_FOLDER "./media/"
#define RESULT "result.txt"
// The path is separated in case the program needs it

#define FILES_AMOUNT 2

typedef struct strFiles {
    char *str;
    struct strFiles *next;
}strFiles_t;
// List of strings from a file

void configFiles(FILE **pText1, FILE **pText2, FILE **pResult, char *argv[]);
char *concat(const char *str1, const char *str2);