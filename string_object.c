#include "string_object.h"
#include <stdlib.h>
#include <string.h>

char* createString(const char* src) {
    if (src == NULL) return NULL;

    char* str = malloc(strlen(src) + 1);
    if (str == NULL) return NULL;

    strcpy(str, src);
    return str;
}

void destroyString(char* str) {
    if (str != NULL) {
        free(str);
    }
}
