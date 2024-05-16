#define MAINLOOP_LIMIT 250
#define LISTLOOP_LIMIT 1000
// Max amount for the loops

typedef enum {
    ERROR_ARGC,
    ERROR_FILE,
    ERROR_MEMORY
}errorEvent_t;
// All error events

void errorHandler(errorEvent_t);