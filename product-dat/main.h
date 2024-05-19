#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>

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
uint8_t choice(const char *_Message, ...);