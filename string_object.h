#ifndef STRING_OBJECT_H
#define STRING_OBJECT_H

#include <stddef.h>
#include <stdbool.h>

typedef struct CString CString;

typedef struct CStringMethods {
    bool (*append)(CString *self, const char *text);
    bool (*append_char)(CString *self, char character);
    void (*clear)(CString *self);
    int (*compare)(const CString *self, const char *text);
    const char *(*c_str)(const CString *self);
    bool (*empty)(const CString *self);
    long (*find)(const CString *self, const char *needle);
    bool (*insert)(CString *self, size_t index, const char *text);
    size_t (*length)(const CString *self);
    bool (*replace)(CString *self, const char *target, const char *replacement);
    bool (*set)(CString *self, const char *text);
    CString *(*substring)(const CString *self, size_t start, size_t count);
    void (*to_lower)(CString *self);
    void (*to_upper)(CString *self);
} CStringMethods;

struct CString {
    char *data;
    size_t length;
    size_t capacity;
    const CStringMethods *methods;
};

CString *string_new(const char *initial_value);
void string_init(CString *string, const char *initial_value);
void string_destroy(CString *string);
void string_delete(CString *string);

#endif
