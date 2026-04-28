#ifndef BOOK_H
#define BOOK_H

typedef struct {
    int id;
    char *title;
    char *author;
    int year;
} Book;

Book *createBook(int id, const char *title, const char *author, int year);
void displayBook(const Book *book);
void destroyBook(Book *book);

#endif