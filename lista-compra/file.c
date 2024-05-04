#include <stdio.h>

#include "./file.h"

void fileAddProduct(product_t *newProduct, FILE **fileList) {
    fseek(*fileList, 0L, SEEK_END);

    fputs("     -----     PRODUCTO     -----\n", *fileList);
    fprintf(*fileList, "Producto: %s\n", newProduct->name);
    fprintf(*fileList, "Cantidad a comprar: %d\n\n", newProduct->cant);
}