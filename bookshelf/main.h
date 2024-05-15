#include <stdint.h>

#define ARGC_PARAMETERS 2
enum {
    ARGV_PATH,
    ARGV_OUTPUT
};

typedef enum {
    ADD_ENTRY = 1,
    PRINT_SPREADSHEET,
    DELETE_ENTRY,
    DELETE_LIST,
    END
}menuState_t;
// States of the menu options

void menu(menuState_t *, FILE **);  /* Loop of the menu */
uint8_t choice(const char *);       /* Returns a bool with a choice */