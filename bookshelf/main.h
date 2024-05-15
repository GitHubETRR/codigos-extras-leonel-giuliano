#include <stdint.h>

#define ARGC_PARAMETERS 2
enum {
    ARGV_PATH,
    ARGV_OUTPUT
};

uint8_t choice(const char *);       /* Returns a bool with a choice */