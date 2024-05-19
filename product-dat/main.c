#include <string.h>

#include "main.h"
#include "product.h"
#include "error.h"

int main(int argc, char *argv[]) {
    if(argc > ARGC_FILE) errorHandler(ERROR_ARGC);

    char *filePath;
    if(argc == ARGC_PRED) filePath = FILE_PRED;
    // Case when the file isn't a parameter
    else filePath = argv[ARGV_FILE];
    // Case when the file is a parameter

    FILE *productDat;
    if((productDat = fopen(filePath, "ab+")) == NULL) errorHandler(ERROR_FILE);

    uint16_t exitPrevent = 0;
    menuState_t menuState;
    do {
        menu(&menuState, productDat, filePath);
        // The state is changed inside the function
        exitPrevent++;
    }while(menuState != MENU_END && exitPrevent != MENU_LOOP);
    // Loops the menu

    fclose(productDat);

    return 0;
}

void menu(menuState_t *state, FILE *productDat, const char *filePath) {
    void (*menuF[MENU_END])(FILE*, const char*) = {
        menuAdd,
        menuPrintProduct,
        menuDelProduct,
        menuEnd
    };
    // Function to work as a switch case

    printf("\n--------------------\n\n");
    printf("%u. Add a product.\n", MENU_ADD);
    printf("%u. Print a selected product.\n", MENU_PRINT_PRODUCT);
    printf("%u. Delete a selected product.\n", MENU_DEL_PRODUCT);
    printf("%u. Exit the code.\n", MENU_END);
    // Prints all the options of the program

    printf("\nChoose an option: ");
    scanf(" %u", state);
    printf("\n");

    if(*state > MENU_START && *state <= MENU_END)
        menuF[*state - 1](productDat, filePath);
    else puts("Select a possible option.");
}

void menuAdd(FILE *productDat, const char *filePath) {
    (void)filePath;
    // Ignores the parameter for the function

    puts("\t-----\tADD PRODUCT\t-----");
    newProduct(productDat);
}

void menuPrintProduct(FILE *productDat, const char *filePath) {
    (void)filePath;
    // Ignores the parameter for the function

    puts("\t-----\tPRINT PRODUCT\t-----");
    printProduct(productDat);
}

void menuDelProduct(FILE *productDat, const char *filePath) {
    if(choice("Do you really meant to delete a product?")) {
        puts("\t-----\tDELETE PRODUCT\t-----");
        setDelProduct(productDat, filePath);
    } else puts("Returning to the menu...");
}

void menuEnd(FILE *productDat, const char *filePath) {
    (void)productDat;
    (void)filePath;
    // Ignores the parameters for the function

    puts("Closing program...");
}

uint8_t choice(const char *str, ...) {
    va_list ap;
    va_start(ap, str);
    // Initialize the variable arguments list

    uint8_t bool = 0;
    char option;

    if(strchr(str, '%') != NULL) vprintf(str, ap);
    else {
        (void)ap;

        printf(str);
    }
    // In case is a simple str, it doesn't use va_list

    printf("\t[y/n]: ");
    scanf(" %c", &option);
    printf("\n");

    if(option == 'y' || option == 'Y') bool = 1;

    va_end(ap);
    return bool;
}