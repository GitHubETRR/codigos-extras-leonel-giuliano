#include <stdio.h>
#include <string.h>

#include "product.h"

void newProduct(FILE *productData) {
    product_t product;
    char tempName[NAME_LENGTH];

    printf("Id of the product: ");
    scanf(" %hu", &product.id);
    printf("Product: ");
    scanf(" %[^\n]", tempName);
    printf("Price: $");
    scanf(" %u", &product.price);
    // Get the data for the product

    strncpy(product.productName, tempName, NAME_LENGTH);
    // Makes sure the other bytes are filled with '\0'

    fwrite(&product, sizeof(product_t), 1, productData);
    fflush(productData);
    // Prints the data to the file
}
