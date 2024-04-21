#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

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
    AGREGAR = 1,
    IMPRIMIR,
    TACHAR,
    ELIMINAR,
    FIN
}menuState_t;

void menu(menuState_t *);
void addProduct(void);

product_t *list = NULL;



int main() {
    menuState_t menuState;

    do { menu(&menuState); } while(menuState != FIN);

    return 0;
}



void menu(menuState_t *menuState) {
    printf("Selecciona: ");
    scanf(" %u", menuState);

    switch (*menuState) {
    case AGREGAR:
        addProduct();

        break;

    default:
        break;
    }
}

void addProduct() {
    product_t *newProduct;
    newProduct = malloc(sizeof(product_t));

    printf("Inserte nombre: ");
    scanf(" %[^\n]%*c", newProduct->name);

    printf("Inserte cantidad: ");
    scanf(" %hhu", &newProduct->cant);

    newProduct->next = list;
    list = newProduct;
}