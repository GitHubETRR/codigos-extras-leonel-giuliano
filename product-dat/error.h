// Exit prevents from the loop
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