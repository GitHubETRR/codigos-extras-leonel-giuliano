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
    if(fread(&productRead, sizeof(product_t), 1, productDat) == 1) {
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
    uint16_t exitPrevent = 0;
    product_t *product = NULL;
    uint16_t id;
    char ch = '\0';

    printf("Id of the product: ");
    scanf(" %hu", &id);
    // Scan the id of the product

    rewind(productDat);
    while(product == NULL && ch != EOF && exitPrevent != READ_LOOP) {
        product = readProduct(productDat, id);

        ch = fgetc(productDat);
        fseek(productDat, -1, SEEK_CUR);
        // Reads the file to know if it's at EOF
        // Goes back in case it wasn't
        exitPrevent++;
    }
    // Searches for the product until the file ends

    if(product != NULL) {
        printf("%d\n", product->id);
        printf("%s\n", product->productName);
        printf("%d\n", product->price);

        free(product);
    }
}

void delProduct(FILE *productDat, const char *filePath) {
    uint16_t exitPrevent = 0;
    FILE *tempFile;
    char *tempPath = "./output/temp.dat";
    // File where the data withouth the product is written
    if(!strcmp(tempPath, filePath)) tempPath = "./output/tempFile.dat";
    // In case they are called the same way

    product_t product;
    uint16_t id;
    uint8_t foundBool = 0;
    char ch = '\0';

    printf("Id of the product: ");
    scanf(" %hu", &id);
    product.id = id + 1;
    // Assure that product.id is different to loop

    if((tempFile = fopen(tempPath, "wb+")) == NULL) {
        fclose(productDat);

        errorHandler(ERROR_FILE);
    }
    // Initialized after the scan so it gets deleted faster

    while(ch != EOF && exitPrevent != READ_LOOP) {
        fread(&product, sizeof(product_t), 1, productDat);

        if(product.id == id) foundBool = 1;
        else fwrite(&product, sizeof(product_t), 1, tempFile);

        ch = fgetc(productDat);
        fseek(productDat, -1, SEEK_CUR);

        exitPrevent++;
    }

    fflush(tempFile);

    if(foundBool) {
        exitPrevent = 0;
        ch = '\0';
        productDat = freopen(filePath, "wb+", productDat);
        // Empty the file

        rewind(tempFile);
        // Make sure is at the beggining
        while(ch != EOF && exitPrevent != READ_LOOP) {
            fread(&product, sizeof(product_t), 1, tempFile);
            fwrite(&product, sizeof(product_t), 1, productDat);
            fflush(productDat);

            ch = fgetc(tempFile);
            fseek(tempFile, -1, SEEK_CUR);
            
            exitPrevent++;
        }
        // Copies the data from a file to the other
    } else printf("The id %d wasn't found.\n", id);

    fclose(tempFile);
    remove(tempPath);
}