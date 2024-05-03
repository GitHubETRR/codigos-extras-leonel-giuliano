#include <stdio.h>
#include <string.h>

#include "./file.h"
#include "../ascii/ascii.h"

void welcome() {
    printf("Bienvenido al programa\n");
    printf(
        "Este c%cdigo realiza la funci%cn de una lista de compras\n",
        oACENTO,
        oACENTO
    );
}

void menu(menuState_t *menuState, product_t **list) {
    FILE *fileList;

    if((fileList = fopen("lista-compra.txt", "w+")) == NULL) {
        printf("\nERROR: No se ha podido acceder a %s", fileList);
        (*menuState) = FIN;

        return;     /* Salida del código si no se abre el archivo */
    }

    printf("\n     -----   MENU   -----\n\n");
    printf(
        "Opci%cn %u: Agrega un producto al inicio de la lista (nombre y cantidad)\n",
        oACENTO,
        AGREGAR
    );
    printf(
        "Opci%cn %u: Anota todos los productos de la lista\n",
        oACENTO,
        IMPRIMIR
    );
    printf(
        "Opci%cn %u: Tacha un producto de la lista\n",
        oACENTO,
        TACHAR
    );
    printf(
        "Opci%cn %u: Elimina todos los productos de la lista\n",
        oACENTO,
        ELIMINAR
    );
    printf(
        "Opci%cn %u: Finaliza el c%cdigo\n\n",
        oACENTO,
        FIN,
        oACENTO
    );
    printf("Selecciona una opci%cn: ", oACENTO);
    scanf(" %u", menuState);
    printf("\n");

    switch (*menuState) {
    case AGREGAR:
        addProduct(list, fileList);
        break;

    case IMPRIMIR:
        printList(list);
        break;

    case TACHAR:
        delProduct(list);
        break;

    case ELIMINAR:
        delList(list);
        break;

    case FIN:
        printf("%cHasta luego!", EXCLAMACION);
        fclose(fileList);

        break;

    default:
        printf("La opci%cn elegida no existe. Inserte otra opci%cn\n", oACENTO, oACENTO);
        printf("Ser%c redirigido al men%c\n", aACENTO, uACENTO);

        break;
    }
}

void addProduct(product_t **list, FILE *fileList) {
    product_t *newProduct;
    newProduct = malloc(sizeof(product_t));

    printf("Anote el nombre del producto: ");
    scanf(" %[^\n]%*c", newProduct->name);

    printf("Anote la cantidad a comprar: ");
    scanf(" %hhu", &newProduct->cant);

    newProduct->next = (*list);
    (*list) = newProduct;

    fileAddProduct(newProduct, fileList);

    printf(
        "\nEl producto '%s' fue a%cadido\n",
        newProduct->name,
        nTILDE
    );
}

void printList(product_t **list) {
    IMPRIMIR_FIN = 0;

    if((*list) == NULL) {
        printf("No hay ning%cn producto en la lista\n", uACENTO);
        return;
    }

    product_t *iProduct;
    iProduct = (*list);

    printf("LISTA:\n");

    while(!IMPRIMIR_FIN) {
        printf("Producto: %s\n", iProduct->name);
        printf("Cantidad: %d\n", iProduct->cant);

        iProduct = iProduct->next;

        if(iProduct == NULL) IMPRIMIR_FIN = 1;
        else printf("\n");
    }
}

void delProduct(product_t **list) {
    TACHAR_FIN = 0;

    if((*list) == NULL) {
        printf("No hay ning%cn producto en la lista\n", uACENTO);
        return;
    }

    char search[NAME_MAX];
    product_t *iProduct, *beforeProduct;
    iProduct = (*list);
    beforeProduct = NULL;

    printf(
        "%cQu%c producto quiere tachar?: ",
        INTERROGACION,
        eACENTO
    );
    scanf(" %[^\n]%*c", search);
    printf("\n");

    while(!TACHAR_FIN) {
        if(strcmp(iProduct->name, search)) {
            beforeProduct = iProduct;
            iProduct = iProduct->next;

            if(iProduct != NULL) continue;

            printf("No se encontr%c el producto\n", oACENTO);
            return;
        } else {
            if(iProduct == (*list)) (*list) = iProduct->next;
            if(beforeProduct != NULL) beforeProduct->next = iProduct->next;

            printf("El producto '%s' ha sido tachado\n", iProduct->name);
            free(iProduct);

            TACHAR_FIN = 1;
        }
    }
}

void delList(product_t **list) {
    if((*list) == NULL) {
        printf("No hay ning%cn producto en la lista\n", uACENTO);
        return;
    }

    freeMemory(list);
    printf("La lista ha sido eliminada\n");
}

void freeMemory(product_t **list) {
    ELIMINAR_FIN = 0;

    while(!ELIMINAR_FIN) {
        product_t *delProduct;
        delProduct = (*list);
        (*list) = delProduct->next;

        free(delProduct);

        if((*list) == NULL) ELIMINAR_FIN = 1;
    }
}