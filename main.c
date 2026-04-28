#include "Book.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100
#define TEXT_SIZE 512
#define FILE_NAME "library.txt"

static Book *library[MAX_BOOKS];
static int book_count = 0;

static void clear_input(void) {
    int c;

    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

static void trim_newline(char *text) {
    size_t len = strlen(text);

    if (len > 0 && text[len - 1] == '\n') {
        text[len - 1] = '\0';
    }
}

static void print_header(void) {
    printf("\n====================================\n");
    printf("          LIBRARY MANAGER\n");
    printf("====================================\n");
}

static void print_menu(void) {
    print_header();
    printf("1. Add Book\n");
    printf("2. Remove Book\n");
    printf("3. Search Book\n");
    printf("4. Display All Books\n");
    printf("5. Save Library\n");
    printf("6. Load Library\n");
    printf("0. Exit\n");
    printf("------------------------------------\n");
    printf("Enter your choice: ");
}

static int book_id_exists(int id) {
    for (int i = 0; i < book_count; i++) {
        if (library[i] != NULL && library[i]->id == id) {
            return 1;
        }
    }

    return 0;
}

static void add_book(void) {
    if (book_count >= MAX_BOOKS) {
        printf("\nLibrary is full.\n");
        return;
    }

    int id;
    int year;
    char title[TEXT_SIZE];
    char author[TEXT_SIZE];

    printf("\nEnter book ID: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid ID.\n");
        clear_input();
        return;
    }
    clear_input();

    if (book_id_exists(id)) {
        printf("A book with this ID already exists.\n");
        return;
    }

    printf("Enter book title: ");
    if (fgets(title, sizeof title, stdin) == NULL) {
        return;
    }
    trim_newline(title);

    if (title[0] == '\0') {
        printf("Title cannot be empty.\n");
        return;
    }

    printf("Enter author name: ");
    if (fgets(author, sizeof author, stdin) == NULL) {
        return;
    }
    trim_newline(author);

    if (author[0] == '\0') {
        printf("Author cannot be empty.\n");
        return;
    }

    printf("Enter publication year: ");
    if (scanf("%d", &year) != 1) {
        printf("Invalid year.\n");
        clear_input();
        return;
    }
    clear_input();

    library[book_count] = createBook(id, title, author, year);

    if (library[book_count] == NULL) {
        printf("Failed to create book.\n");
        return;
    }

    book_count++;
    printf("\nBook added successfully.\n");
}

static void remove_book(void) {
    if (book_count == 0) {
        printf("\nNo books in the library.\n");
        return;
    }

    int id;

    printf("\nEnter book ID to remove: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid ID.\n");
        clear_input();
        return;
    }
    clear_input();

    for (int i = 0; i < book_count; i++) {
        if (library[i] != NULL && library[i]->id == id) {
            destroyBook(library[i]);

            for (int j = i; j < book_count - 1; j++) {
                library[j] = library[j + 1];
            }

            library[book_count - 1] = NULL;
            book_count--;

            printf("\nBook removed successfully.\n");
            return;
        }
    }

    printf("\nBook not found.\n");
}

static void search_book(void) {
    if (book_count == 0) {
        printf("\nNo books in the library.\n");
        return;
    }

    int id;

    printf("\nEnter book ID to search: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid ID.\n");
        clear_input();
        return;
    }
    clear_input();

    for (int i = 0; i < book_count; i++) {
        if (library[i] != NULL && library[i]->id == id) {
            printf("\nBook found:\n");
            printf("------------------------------------\n");
            displayBook(library[i]);
            return;
        }
    }

    printf("\nBook not found.\n");
}

static void display_books(void) {
    if (book_count == 0) {
        printf("\nNo books in the library.\n");
        return;
    }

    printf("\n========== ALL BOOKS ==========\n");

    for (int i = 0; i < book_count; i++) {
        printf("\nBook %d\n", i + 1);
        printf("------------------------------------\n");
        displayBook(library[i]);
    }
}

static void save_library(void) {
    FILE *file = fopen(FILE_NAME, "w");

    if (file == NULL) {
        printf("\nCould not open file for saving.\n");
        return;
    }

    for (int i = 0; i < book_count; i++) {
        fprintf(file, "%d|%s|%s|%d\n",
                library[i]->id,
                library[i]->title,
                library[i]->author,
                library[i]->year);
    }

    fclose(file);
    printf("\nLibrary saved successfully to %s.\n", FILE_NAME);
}

static void clear_library(void) {
    for (int i = 0; i < book_count; i++) {
        destroyBook(library[i]);
        library[i] = NULL;
    }

    book_count = 0;
}

static void load_library(void) {
    FILE *file = fopen(FILE_NAME, "r");

    if (file == NULL) {
        printf("\nNo saved library file found.\n");
        return;
    }

    clear_library();

    char line[1200];

    while (fgets(line, sizeof line, file) != NULL && book_count < MAX_BOOKS) {
        trim_newline(line);

        char *id_text = strtok(line, "|");
        char *title = strtok(NULL, "|");
        char *author = strtok(NULL, "|");
        char *year_text = strtok(NULL, "|");

        if (id_text == NULL || title == NULL || author == NULL || year_text == NULL) {
            continue;
        }

        int id = atoi(id_text);
        int year = atoi(year_text);

        library[book_count] = createBook(id, title, author, year);

        if (library[book_count] != NULL) {
            book_count++;
        }
    }

    fclose(file);
    printf("\nLibrary loaded successfully. %d book(s) loaded.\n", book_count);
}

int main(void) {
    int choice;

    load_library();

    do {
        print_menu();

        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid input. Please enter a number.\n");
            clear_input();
            continue;
        }
        clear_input();

        switch (choice) {
            case 1:
                add_book();
                break;
            case 2:
                remove_book();
                break;
            case 3:
                search_book();
                break;
            case 4:
                display_books();
                break;
            case 5:
                save_library();
                break;
            case 6:
                load_library();
                break;
            case 0:
                save_library();
                printf("\nExiting program. Goodbye.\n");
                break;
            default:
                printf("\nInvalid choice. Try again.\n");
        }

    } while (choice != 0);

    clear_library();

    return 0;
}