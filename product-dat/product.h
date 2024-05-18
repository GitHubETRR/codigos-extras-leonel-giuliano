#include <stdio.h>
#include <stdint.h>

#define NAME_LENGTH 30
// Because uint16 has to be in a multiple of 2 direction
// And uint32 in a multiple of 4
// The length of the name has to make
// (2 + NAME_LENGTH + 4) % 4 = 0 o NAME_LENGTH = 2n + 4

typedef struct {
    uint16_t id;
    // Number to search
    char productName[NAME_LENGTH];
    // Name of the product
    uint32_t price;
}product_t;
// Struct for the products

void newProduct(FILE *);