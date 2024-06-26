#include <stdio.h>
#include <stdint.h>

#define NAME_LENGTH 30
// Because uint16 has to be in a multiple of 2 direction
// And uint32 in a multiple of 4
// (2 + NAME_LENGTH) % 4 = 0 => NAME_LENGTH = 4n + 2
// NAME_LENGTH = 2(2n + 1), the double of any odd num

typedef struct {
    uint16_t id;
    // Number to search
    char productName[NAME_LENGTH];
    // Name of the product
    uint32_t price;
}product_t;
// Struct for the products

void newProduct(FILE *_Stream);
product_t *readProduct(FILE *_Stream, uint16_t _Id);
void printProduct(FILE *_Stream);
void printFile(FILE *_Stream);
void backup(FILE *_Stream);
void delProduct(FILE *_FileStream, FILE *_TempStream, const char *_FilePath, uint16_t _Id);
void setDelProduct(FILE *_Stream, const char *_FileName);