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
void printList(void);
void delProduct(void);

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

    case IMPRIMIR:
        printList();
        break;

    case TACHAR:
        delProduct();
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

void printList() {
    IMPRIMIR_FIN = 0;

    if(list == NULL) {
        printf("No hay ning%cn producto\n", uACENTO);
        return;
    }

    product_t *iProduct;
    iProduct = list;

    while(!IMPRIMIR_FIN) {
        printf("Producto: %s\n", iProduct->name);
        printf("Cantidad: %d\n", iProduct->cant);

        iProduct = iProduct->next;

        if(iProduct == NULL) IMPRIMIR_FIN = 1;
    }
}

void delProduct() {
    TACHAR_FIN = 0;

    if(list == NULL) {
        printf("No hay ning%cn producto\n", uACENTO);
        return;
    }

    char search[NAME_MAX];
    product_t *iProduct, *beforeProduct;
    iProduct = list;
    beforeProduct = NULL;

    printf(
        "%cQu%c producto busca?: ",
        INTERROGACION,
        eACENTO
    );
    scanf(" %[^\n]%*c", search);

    while(!TACHAR_FIN) {
        if(strcmp(iProduct->name, search)) {
            beforeProduct = iProduct;       /* CAMBIAR EN DIAGRAMA */
            iProduct = iProduct->next;

            if(iProduct != NULL) continue;

            printf("No se encontr%c el producto\n", oACENTO);
            return;
        } else {
            if(iProduct == list) list = iProduct->next;
            if(beforeProduct != NULL) beforeProduct->next = iProduct->next; /* CAMBIAR EN DIAGRAMA */

            free(iProduct);
            printf("Tachado\n");
            TACHAR_FIN = 1;
        }
    }
}