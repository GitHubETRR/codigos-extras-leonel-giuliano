#define EXIT_PREVENT 5000
// Max amount of recursion for the books in case of an error

typedef enum {
    ERROR_ARGC,
    ERROR_FILE,
    ERROR_MEMORY
}errorEvent_t;
// All error events

void errorHandler(errorEvent_t);