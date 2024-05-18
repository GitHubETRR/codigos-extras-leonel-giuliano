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

int main(int argc, char *argv[]) {
    if(argc > ARGC_FILE) errorHandler(ERROR_ARGC);

    char *filePath;
    if(argc == ARGC_PRED) filePath = FILE_PRED;
    else filePath = argv[ARGV_FILE];

    FILE *productDat;
    if((productDat = fopen(filePath, "ab+")) == NULL) errorHandler(ERROR_FILE);

    newProduct(productDat);

    return 0;
}