// Exit prevents from the loop
#define MENU_LOOP 500
#define READ_LOOP 5000

typedef enum {
    ERROR_ARGC,
    ERROR_FILE,
    ERROR_FILEREMOVE,
    ERROR_FILEREAD,
    ERROR_MEMORY
}errorEvent_t;
// Every possible error

void errorHandler(errorEvent_t _Error);