#include <stdio.h>

#include "./file.h"

void fileAddProduct(product_t *newProduct, FILE *fileList) {
    static uint8_t iProduct = 1;

    fprintf(fileList, "     -----     PRODUCTO %d     -----\n", iProduct);
    fprintf(fileList, "Producto: %s\n", newProduct->name);
    fprintf(fileList, "Cantidad a comprar: %d\n\n", newProduct->cant);

    iProduct++;
}