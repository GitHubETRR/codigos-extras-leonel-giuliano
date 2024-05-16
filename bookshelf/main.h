#include <stdint.h>

#define ARGC_PARAMETERS 2
enum {
    ARGV_PATH,
    ARGV_OUTPUT
};

typedef enum {
    MENU_START,
    ADD_ENTRY,
    PRINT_NEW_ENTRIES,
    DELETE_ENTRY,
    DELETE_LIST,
    MENU_END
}menuState_t;
// States of the menu options

void menu(menuState_t *, FILE **);  /* Loop of the menu */
void menuDelEntry(FILE **);         /* Functions to delete an entry */
uint8_t choice(const char *);       /* Returns a bool with a choice */