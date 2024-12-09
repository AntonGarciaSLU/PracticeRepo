#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/library.h"
#define MAX_BOOKS 100
#define MAX_TITLE_LENGTH 100
#define MAX_AUTHOR_LENGTH 50

typedef struct {
    char title[MAX_TITLE_LENGTH];
    char author[MAX_AUTHOR_LENGTH];
} Book;

// Helper function to display all books
static void displayBooks(const char *filename, Book *books, int *count) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open %s\n", filename);
        return;
    }

    *count = 0;
    while (fscanf(file, "%[^,],%[^\n]\n", books[*count].title, books[*count].author) != EOF) {
        if (strlen(books[*count].author) == 0) {
            strcpy(books[*count].author, "Unknown Author");
        }
        printf("%d. %s by %s\n", (*count) + 1, books[*count].title, books[*count].author);
        (*count)++;
    }
    fclose(file);
}

// Helper function to write updated list of books back to the file
static void writeBooks(const char *filename, Book *books, int count) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error: Could not open %s for writing\n", filename);
        return;
    }

    for (int i = 0; i < count; ++i) {
        fprintf(file, "%s,%s\n", books[i].title, books[i].author);
    }
    fclose(file);
}

// Function to borrow a book
void borrowBook() {
    Book books[MAX_BOOKS];
    int count = 0, choice;

    printf("\nAvailable Books:\n");
    displayBooks("books.txt", books, &count);

    if (count == 0) {
        printf("No books available to borrow.\n");
        return;
    }

    printf("Enter the number of the book you want to borrow: ");
    if (scanf("%d", &choice) != 1 || choice < 1 || choice > count) {
        printf("Invalid choice. Try again.\n");
        while (getchar() != '\n'); // Clear invalid input
        return;
    }

    FILE *borrowedFile = fopen("BorrowedBooks.txt", "a");
    if (!borrowedFile) {
        printf("Error: Could not open BorrowedBooks.txt\n");
        return;
    }
    fprintf(borrowedFile, "%s,%s\n", books[choice - 1].title, books[choice - 1].author);
    fclose(borrowedFile);

    printf("You borrowed: %s by %s\n", books[choice - 1].title, books[choice - 1].author);

    // Remove the borrowed book from available list
    for (int i = choice - 1; i < count - 1; ++i) {
        books[i] = books[i + 1];
    }
    count--;

    writeBooks("books.txt", books, count);
}

// Function to return a borrowed book
void returnBook() {
    Book books[MAX_BOOKS];
    int count = 0, choice;

    printf("\nBorrowed Books:\n");
    displayBooks("BorrowedBooks.txt", books, &count);

    if (count == 0) {
        printf("No borrowed books to return.\n");
        return;
    }

    printf("Enter the number of the book you want to return: ");
    if (scanf("%d", &choice) != 1 || choice < 1 || choice > count) {
        printf("Invalid choice. Try again.\n");
        while (getchar() != '\n'); // Clear invalid input
        return;
    }

    FILE *file = fopen("books.txt", "a");
    if (!file) {
        printf("Error: Could not open books.txt\n");
        return;
    }
    fprintf(file, "%s,%s\n", books[choice - 1].title, books[choice - 1].author);
    fclose(file);

    // Remove the returned book from borrowed list
    for (int i = choice - 1; i < count - 1; ++i) {
        books[i] = books[i + 1];
    }
    count--;

    writeBooks("BorrowedBooks.txt", books, count);
    printf("You returned: %s by %s\n", books[choice - 1].title, books[choice - 1].author);
}

// Function to donate a book
void donateBook() {
    FILE *file;
    char book[MAX_TITLE_LENGTH + MAX_AUTHOR_LENGTH];

    printf("\nEnter the title and author of the book you want to donate (e.g., 'The Catcher in the Rye,J.D. Salinger'): ");
    getchar();
    if (fgets(book, sizeof(book), stdin) == NULL) {
        printf("Error: Could not read input.\n");
        return;
    }

    file = fopen("books.txt", "a");
    if (file == NULL) {
        printf("Error: Could not open books.txt\n");
        return;
    }
    fprintf(file, "%s", book);
    fclose(file);

    printf("Thank you for donating: %s", book);
}

// Function to search for a book
void searchBook() {
    FILE *file;
    char query[MAX_TITLE_LENGTH];
    char line[MAX_TITLE_LENGTH + MAX_AUTHOR_LENGTH];
    int found = 0;

    printf("\nEnter the title or keyword to search for: ");
    getchar();
    if (fgets(query, MAX_TITLE_LENGTH, stdin) == NULL) {
        printf("Error: Could not read input.\n");
        return;
    }
    query[strcspn(query, "\n")] = '\0';

    file = fopen("books.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open books.txt\n");
        return;
    }

    printf("\nSearch Results:\n");
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, query) != NULL) {
            printf("%s", line);
            found = 1;
        }
    }
    fclose(file);

    if (!found) {
        printf("No books found matching the query.\n");
    }
}

// Function to list all books
void listBooks() {
    Book books[MAX_BOOKS];
    int count = 0;

    printf("\nAll Available Books:\n");
    displayBooks("books.txt", books, &count);
}

// Function to update book details
void updateBookDetails() {
    Book books[MAX_BOOKS];
    int count = 0, choice;
    char newTitle[MAX_TITLE_LENGTH], newAuthor[MAX_AUTHOR_LENGTH];

    printf("\nAvailable Books:\n");
    displayBooks("books.txt", books, &count);

    if (count == 0) {
        printf("No books available to update.\n");
        return;
    }

    printf("Enter the number of the book you want to update: ");
    if (scanf("%d", &choice) != 1 || choice < 1 || choice > count) {
        printf("Invalid choice. Try again.\n");
        return;
    }

    printf("Enter the new title: ");
    getchar();
    if (fgets(newTitle, MAX_TITLE_LENGTH, stdin) == NULL) {
        printf("Error: Could not read input.\n");
        return;
    }
    newTitle[strcspn(newTitle, "\n")] = '\0';

    printf("Enter the new author: ");
    if (fgets(newAuthor, MAX_AUTHOR_LENGTH, stdin) == NULL) {
        printf("Error: Could not read input.\n");
        return;
    }
    newAuthor[strcspn(newAuthor, "\n")] = '\0';

    // Update the book details
    strcpy(books[choice - 1].title, newTitle);
    strcpy(books[choice - 1].author, newAuthor);

    writeBooks("books.txt", books, count);
    printf("Book details updated successfully.\n");
}

// Function to set a due date for a borrowed book
void setDueDate() {
    Book books[MAX_BOOKS];
    int count = 0, choice;
    char dueDate[11];

    printf("\nBorrowed Books:\n");
    displayBooks("BorrowedBooks.txt", books, &count);

    if (count == 0) {
        printf("No borrowed books to set a due date for.\n");
        return;
    }

    printf("Enter the number of the book you want to set a due date for: ");
    if (scanf("%d", &choice) != 1 || choice < 1 || choice > count) {
        printf("Invalid choice. Try again.\n");
        return;
    }

    printf("Enter the due date (YYYY-MM-DD): ");
    getchar();
    if (fgets(dueDate, 11, stdin) == NULL) {
        printf("Error: Could not read input.\n");
        return;
    }
    dueDate[strcspn(dueDate, "\n")] = '\0';

    // Update the borrowed book with the due date
    FILE *tempFile = fopen("temp.txt", "w");
    if (!tempFile) {
        printf("Error: Could not create temp file.\n");
        return;
    }

    FILE *borrowedFile = fopen("BorrowedBooks.txt", "r");
    if (!borrowedFile) {
        printf("Error: Could not open BorrowedBooks.txt\n");
        fclose(tempFile);
        return;
    }

    for (int i = 0; i < count; ++i) {
        if (i == choice - 1) {
            fprintf(tempFile, "%s,%s (%s)\n", books[i].title, books[i].author, dueDate);
        } else {
            fprintf(tempFile, "%s,%s\n", books[i].title, books[i].author);
        }
    }

    fclose(borrowedFile);
    fclose(tempFile);

    remove("BorrowedBooks.txt");
    rename("temp.txt", "BorrowedBooks.txt");

    printf("Due date set successfully for: %s by %s\n", books[choice - 1].title, books[choice - 1].author);
}

// Function to remove a book from the library
void removeBook() {
    Book books[MAX_BOOKS];
    int count = 0, choice;

    printf("\nAvailable Books:\n");
    displayBooks("books.txt", books, &count);

    if (count == 0) {
        printf("No books available to remove.\n");
        return;
    }

    printf("Enter the number of the book you want to remove: ");
    if (scanf("%d", &choice) != 1 || choice < 1 || choice > count) {
        printf("Invalid choice. Try again.\n");
        return;
    }

    // Remove the book from the list
    for (int i = choice - 1; i < count - 1; ++i) {
        books[i] = books[i + 1];
    }
    count--;

    writeBooks("books.txt", books, count);
    printf("Book removed successfully.\n");
}


