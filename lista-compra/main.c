#include <stdio.h>

#include "./lista-compra.h"

int main() {
    product_t *list = NULL;
    menuState_t menuState;

    welcome();
    do { menu(&menuState, &list); } while(menuState != FIN);
    if(list != NULL) freeMemory(&list);

    return 0;
}