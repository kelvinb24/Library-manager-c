#include "Book.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *dup_string(const char *src) {
    if (src == NULL) {
        return NULL;
    }

    size_t len = strlen(src) + 1;
    char *copy = malloc(len);

    if (copy != NULL) {
        memcpy(copy, src, len);
    }

    return copy;
}

Book *createBook(int id, const char *title, const char *author, int year) {
    Book *book = malloc(sizeof *book);

    if (book == NULL) {
        return NULL;
    }

    book->id = id;
    book->title = dup_string(title);
    book->author = dup_string(author);
    book->year = year;

    if ((title != NULL && book->title == NULL) ||
        (author != NULL && book->author == NULL)) {
        destroyBook(book);
        return NULL;
        }

    return book;
}

void displayBook(const Book *book) {
    if (book == NULL) {
        printf("No book data available.\n");
        return;
    }

    printf("ID: %d\n", book->id);
    printf("Title: %s\n", book->title);
    printf("Author: %s\n", book->author);
    printf("Year: %d\n", book->year);
}

void destroyBook(Book *book) {
    if (book == NULL) {
        return;
    }

    free(book->title);
    free(book->author);
    free(book);
}