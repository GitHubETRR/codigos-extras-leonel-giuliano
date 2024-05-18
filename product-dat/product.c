#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "product.h"
#include "error.h"

void newProduct(FILE *productDat) {
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

    fwrite(&product, sizeof(product_t), 1, productDat);
    fflush(productDat);
    // Prints the data to the file
}

product_t *readProduct(FILE *productDat, uint16_t id) {
    product_t *productReturn;
    if((productReturn = (product_t*)malloc(sizeof(product_t))) == NULL) {
        fclose(productDat);
        errorHandler(ERROR_MEMORY);
    }

    product_t productRead;
    if(fread(&productRead, sizeof(product_t), 1, productDat) != 0) {
        if(productRead.id == id) *productReturn = productRead;
        else productReturn = NULL;
    } else {
        free(productReturn);
        fclose(productDat);

        errorHandler(ERROR_FILEREAD);
    }
    // Read the product from a position
    // In case there was a problem reading it, exit the code

    return productReturn;
    // Retuns the product in case it was found
    // Returns NULL in case the id wasn't found
}