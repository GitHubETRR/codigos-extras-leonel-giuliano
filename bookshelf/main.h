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

// FLAGS
#define ENTRY_FOUND flags.data.bit0     /* Entry found inside of the file */

union {
    struct {
        unsigned int bit0 : 1;
        unsigned int bit1 : 1;
        unsigned int bit2 : 1;
        unsigned int bit3 : 1;
        unsigned int bit4 : 1;
        unsigned int bit5 : 1;
        unsigned int bit6 : 1;
        unsigned int bit7 : 1;
    }data;

    uint8_t space;
}flags;

void menu(menuState_t *, FILE **);  /* Loop of the menu */
void menuDelEntry(FILE **);         /* Functions to delete an entry */
uint8_t choice(const char *);       /* Returns a bool with a choice */