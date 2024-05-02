#include <stdio.h>

#include "./lista-compra.h"

int main() {
    menuState_t menuState;

    welcome();
    do { menu(&menuState); } while(menuState != FIN);
    if(list != NULL) freeMemory();

    return 0;
}