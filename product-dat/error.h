// Exit prevents from the loop
#define MENU_LOOP 500
#define CHOICE_LOOP 50
#define READ_LOOP 2000

typedef enum {
    ERROR_ARGC,
    ERROR_FILE,
    ERROR_FILEREMOVE,
    ERROR_MEMORY
}errorEvent_t;
// Every possible error

void errorHandler(errorEvent_t _Error);