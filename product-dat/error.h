typedef enum {
    ERROR_ARGC,
    ERROR_FILE,
    ERROR_MEMORY
}errorEvent_t;
// Every possible error

void errorHandler(errorEvent_t);