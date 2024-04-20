#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "../ascii/ascii.h"

#define NAME_MAX 30

#define IMPRIMIR_FIN flags.flag.bit0
#define TACHAR_FIN flags.flag.bit1
#define ELIMINAR_FIN flags.flag.bit2

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
    }flag;

    uint8_t byte;
}flags;

typedef struct product {
    char name[NAME_MAX];
    uint8_t cant;
    struct product *next;
}product_t;

typedef enum {
    AGREGAR,
    IMPRIMIR,
    TACHAR,
    ELIMINAR,
    FIN
}menuState_t;