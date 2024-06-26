#include <stdlib.h>
#include <string.h>

#include "product.h"
#include "main.h"
#include "error.h"

void newProduct(FILE *productDat) {
    product_t product;
    char tempName[NAME_LENGTH];

    printf("Id of the product: ");
    scanf(" %hu", &(product.id));
    printf("Product: ");
    scanf(" %29[^\n]", tempName);
    // Only takes NAME_LENGTH - 1 chars in case of an error
    char ch;
    while((ch = getchar()) != '\n' && ch != EOF);
    // Makes sure that the data doesn't get save and
    // goes to another scan in case the text is longer
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
    
    fread(&productRead, sizeof(product_t), 1, productDat);

    if(productRead.id == id) *productReturn = productRead;
    else productReturn = NULL;
    // Read the product from a position

    return productReturn;
    // Retuns the product in case it was found
    // Returns NULL in case the id wasn't found
}

void printProduct(FILE *productDat) {
    uint16_t exitPrevent = 0;
    product_t *product = NULL;
    uint16_t id;
    char ch;

    printf("Id of the product: ");
    scanf(" %hu", &id);
    printf("\n");
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
        printf("Product: %s\n", product->productName);
        printf("Price: $%d\n", product->price);

        free(product);
    } else printf("The product id %d wasn't found.\n", id);
}

void printFile(FILE *productDat) {
    uint16_t exitPrevent = 0;
    product_t product;

    rewind(productDat);
    while(fread(&product, sizeof(product_t), 1, productDat) && exitPrevent != READ_LOOP) {
        printf("Id: %d\n", product.id);
        printf("Product: %s\n", product.productName);
        printf("Price: $%d\n", product.price);
        printf("++++++++++++++++++++\n");

        exitPrevent++;
    }
}

void backup(FILE *productDat) {
    uint16_t exitPrevent = 0;
    FILE *backFile;
    product_t product;
    char backPath[PATH_LENGTH];

    printf("Write the path of the backup file: ");
    scanf(" %259s", backPath);
    // The output of the backup is selected
    char ch;
    while((ch = getchar()) != '\n' && ch != EOF);
    // Prevent overflow inside the buffer

    size_t pathLength = strlen(backPath);
    if(strcmp(&backPath[pathLength - strlen(FILE_TYPE)], FILE_TYPE))
        printf("The backup has to correspond with the '%s' type file.\n", FILE_TYPE);
    // In case the file isn't .dat, it doesn't create the backup
    else {
        if((backFile = fopen(backPath, "wb")) == NULL) {
            fclose(productDat);

            errorHandler(ERROR_FILE);
        }

        while(fread(&product, sizeof(product_t), 1, productDat) && exitPrevent != READ_LOOP) {
            fwrite(&product, sizeof(product_t), 1, backFile);

            exitPrevent++;
        }

        fflush(backFile);
        fclose(backFile);
    }
}

void delProduct(FILE *productDat, FILE *tempFile, const char *filePath, uint16_t id) {
    uint16_t exitPrevent = 0;
    uint8_t foundBool = 0;
    product_t product;
    product.id = id + 1;
    // Makes sure that product.id is different to loop

    rewind(productDat);
    while(fread(&product, sizeof(product_t), 1, productDat) && exitPrevent != READ_LOOP) {
        if(product.id == id) foundBool = 1;
        else fwrite(&product, sizeof(product_t), 1, tempFile);

        exitPrevent++;
    }

    fflush(tempFile);

    if(foundBool) {
        exitPrevent = 0;
        productDat = freopen(filePath, "wb+", productDat);
        // Empty the file

        rewind(tempFile);
        // Make sure is at the beggining
        while(fread(&product, sizeof(product_t), 1, tempFile) && exitPrevent != READ_LOOP) {
            fwrite(&product, sizeof(product_t), 1, productDat);
            fflush(productDat);
            
            exitPrevent++;
        }
        // Copies the data from a file to the other
    } else printf("The id %d wasn't found.\n", id);
}

void setDelProduct(FILE *productDat, const char *filePath) {
    FILE *tempFile;
    char *tempPath = "./output/temp.dat";
    // File where the data withouth the product is written
    if(!strcmp(tempPath, filePath)) tempPath = "./output/tempFile.dat";
    // In case they are called the same way

    uint8_t exitPrevent = 0;
    uint16_t id;
    uint8_t option = 0;

    while(option == 0 && exitPrevent != CHOICE_LOOP) {
        printf("Id of the product: ");
        scanf(" %hu", &id);

        option = choice("\nDo you want to delete the product id %d?", id);
        exitPrevent++;
    }

    if((tempFile = fopen(tempPath, "wb+")) == NULL) {
        fclose(productDat);

        errorHandler(ERROR_FILE);
    }
    // Initialized after the scan so it gets deleted faster
    delProduct(productDat, tempFile, filePath, id);

    fclose(tempFile);
    remove(tempPath);
}