#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "product.h"
#include "error.h"

void newProduct(FILE *productDat) {
    product_t product;
    char tempName[NAME_LENGTH];

    printf("Id of the product: ");
    scanf(" %hu", &(product.id));
    printf("Product: ");
    scanf(" %[^\n]", tempName);
    printf("Price: $");
    scanf(" %u", &(product.price));
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
    if(!fread(&productRead, sizeof(product_t), 1, productDat)) {
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

void printProduct(FILE *productDat) {
    product_t *product = NULL;
    uint16_t id;
    char ch = '\0';

    printf("Id of the product: ");
    scanf(" %hu", &id);
    // Scan the id of the product

    rewind(productDat);
    while(product == NULL && ch != EOF) {
        product = readProduct(productDat, id);

        ch = fgetc(productDat);
        fseek(productDat, -1, SEEK_CUR);
        // Reads the file to know if it's at EOF
        // Goes back in case it wasn't
    }
    // Searches for the product until the file ends

    if(product != NULL) {
        printf("%d\n", product->id);
        printf("%s\n", product->productName);
        printf("%d\n", product->price);

        free(product);
    }
}