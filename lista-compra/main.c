#include <stdio.h>

#include "./lista-compra.h"
#include "../ascii/ascii.h"

void welcome();

int main() {
    FILE *fileList;
    char *fileName = "lista-compra.txt";

    if((fileList = fopen(fileName, "w")) == NULL) {
        printf("No se ha podido acceder a '%s'", fileName);

        return 1;
    }

    product_t *list = NULL;
    menuState_t menuState;

    welcome();
    menuLoop(&list, &fileList);
    // do { menu(&menuState, &list); } while(menuState != FIN);
    if(list != NULL) freeMemory(&list);

    fclose(fileList);

    return 0;
}

void welcome() {
    printf("Bienvenido al programa\n");
    printf(
        "Este c%cdigo realiza la funci%cn de una lista de compras\n",
        oACENTO,
        oACENTO
    );
}