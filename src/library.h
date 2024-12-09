#ifndef LIBRARY_H
#define LIBRARY_H

#define MAX_BOOKS 100
#define MAX_TITLE_LENGTH 100
#define MAX_AUTHOR_LENGTH 50

typedef struct {
    char title[MAX_TITLE_LENGTH];
    char author[MAX_AUTHOR_LENGTH];
    char dueDate[11];
} Book;

void borrowBook();
void returnBook();
void donateBook();
void searchBook();
void listBooks();
void updateBookDetails();
void setDueDate();
void removeBook();

#endif