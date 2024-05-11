#include <stdio.h>

#include "mallist.h"

int main(void) {
    char *ptr = (char*)mallist(sizeof(char));
    *ptr = 'a';

    printf("%u\n", *ptr);
    freePtr(ptr);
    printf("%u\n", *ptr);

    return 0;
}