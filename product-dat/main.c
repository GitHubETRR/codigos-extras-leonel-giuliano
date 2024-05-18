#include <stdio.h>

#include "product.h"
#include "error.h"

#define FILE_PRED "./output/product.dat"
enum {
    ARGC_PRED = 1,
    ARGC_FILE
};
// Doesn't need the file path
enum {
    ARGV_PATH,
    ARGV_FILE
};

typedef enum {
    MENU_START,
    MENU_ADD,
    MENU_PRINT_PRODUCT,
    MENU_DEL_PRODUCT,
    MENU_END
}menuState_t;
// All the states of the menu

void menu(menuState_t *_State, FILE *_Stream, const char *_FilePath);
void menuAdd(FILE *_Stream, const char *_FilePath);
void menuPrintProduct(FILE *_Stream, const char *_FilePath);
void menuDelProduct(FILE *_Stream, const char *_FilePath);
void menuEnd(FILE *_Stream, const char *_FilePath);

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

    printf("%u. Add a product.\n", MENU_ADD);
    printf("%u. Print a selected product.\n", MENU_PRINT_PRODUCT);
    printf("%u. Delete a selected product.\n", MENU_DEL_PRODUCT);
    printf("%u. Exit the code.\n", MENU_END);
    // Prints all the options of the program

    printf("\nChoose an option: ");
    scanf(" %u", state);

    if(*state > MENU_START && *state <= MENU_END)
        menuF[*state - 1](productDat, filePath);
    else puts("Select a possible option.");
}

void menuAdd(FILE *productDat, const char *filePath) {
    (void)filePath;
    // Ignores the parameter for the function
    newProduct(productDat);
}

void menuPrintProduct(FILE *productDat, const char *filePath) {
    (void)filePath;
    printProduct(productDat);
}

void menuDelProduct(FILE *productDat, const char *filePath) {
    setDelProduct(productDat, filePath);
}

void menuEnd(FILE *productDat, const char *filePath) {
    (void)productDat;
    (void)filePath;
    puts("Closing program...");
}