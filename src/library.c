#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

// Function to borrow a book
void borrowBook() {
    FILE *file, *borrowedFile, *tempFile;
    Book books[MAX_BOOKS];
    int count = 0, choice, i;

    file = fopen("books.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open books.txt\n");
        return;
    }

    printf("\nAvailable Books:\n");
    while (fscanf(file, "%[^,],%[^\n]\n", books[count].title, books[count].author) != EOF) {
        // Ensure the author is not empty
        if (strlen(books[count].author) == 0) {
            strcpy(books[count].author, "Unknown Author");
        }
        printf("%d. %s by %s\n", count + 1, books[count].title, books[count].author);
        count++;
    }
    fclose(file);

    if (count == 0) {
        printf("No books available.\n");
        return;
    }

    printf("\nEnter the number of the book you want to borrow: ");
    if (scanf("%d", &choice) != 1 || choice < 1 || choice > count) {
        printf("Invalid choice. Please enter a valid number.\n");
        return;
    }

    borrowedFile = fopen("BorrowedBooks.txt", "a");
    if (borrowedFile == NULL) {
        printf("Error: Could not open BorrowedBooks.txt\n");
        return;
    }
    fprintf(borrowedFile, "%s by %s\n", books[choice - 1].title, books[choice - 1].author);
    fclose(borrowedFile);

    tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error: Could not create temp file.\n");
        return;
    }

    file = fopen("books.txt", "r");
    for (i = 0; i < count; i++) {
        if (i != choice - 1) {
            fprintf(tempFile, "%s,%s\n", books[i].title, books[i].author);
        }
    }
    fclose(file);
    fclose(tempFile);

    remove("books.txt");
    rename("temp.txt", "books.txt");

    printf("You have borrowed: %s by %s\n", books[choice - 1].title, books[choice - 1].author);
}

// Function to return a borrowed book
void returnBook() {
    FILE *borrowedFile, *tempFile, *file;
    Book books[MAX_BOOKS];
    int count = 0, choice, i;

    borrowedFile = fopen("BorrowedBooks.txt", "r");
    if (borrowedFile == NULL) {
        printf("No borrowed books found.\n");
        return;
    }

    printf("\nBorrowed Books:\n");
    while (fscanf(borrowedFile, "%[^,],%[^\n]\n", books[count].title, books[count].author) != EOF) {
        printf("%d. %s by %s\n", count + 1, books[count].title, books[count].author);
        count++;
    }
    fclose(borrowedFile);

    if (count == 0) {
        printf("No books to return.\n");
        return;
    }

    printf("\nEnter the number of the book you want to return: ");
    if (scanf("%d", &choice) != 1 || choice < 1 || choice > count) {
        printf("Invalid choice. Please enter a valid number.\n");
        return;
    }

    file = fopen("books.txt", "a");
    if (file == NULL) {
        printf("Error: Could not open books.txt\n");
        return;
    }
    fprintf(file, "%s by %s\n", books[choice - 1].title, books[choice - 1].author);
    fclose(file);

    tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error: Could not create temp file.\n");
        return;
    }

    borrowedFile = fopen("BorrowedBooks.txt", "r");
    for (i = 0; i < count; i++) {
        if (i != choice - 1) {
            fprintf(tempFile, "%s,%s\n", books[i].title, books[i].author);
        }
    }
    fclose(borrowedFile);
    fclose(tempFile);

    remove("BorrowedBooks.txt");
    rename("temp.txt", "BorrowedBooks.txt");

    printf("You have returned: %s by %s\n", books[choice - 1].title, books[choice - 1].author);
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
    FILE *file;
    Book books[MAX_BOOKS];
    int count = 0;

    file = fopen("books.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open books.txt\n");
        return;
    }

    printf("\nAll Available Books:\n");
    while (fscanf(file, "%[^,],%[^\n]\n", books[count].title, books[count].author) != EOF) {
        // Trim extra spaces from the author name
        char *author_end = books[count].author + strlen(books[count].author) - 1;
        while (author_end > books[count].author && (*author_end == ' ' || *author_end == '\n')) {
            *author_end-- = '\0';
        }
        // Handle missing authors
        if (strlen(books[count].author) == 0) {
            printf("%d. %s\n", count + 1, books[count].title);
        } else {
            printf("%d. %s by %s\n", count + 1, books[count].title, books[count].author);
        }
        count++;
    }
    fclose(file);
}


// Function to update book details
void updateBookDetails() {
    FILE *file, *tempFile;
    Book books[MAX_BOOKS];
    int count = 0, choice, i;
    char newTitle[MAX_TITLE_LENGTH], newAuthor[MAX_AUTHOR_LENGTH];

    file = fopen("books.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open books.txt\n");
        return;
    }

    printf("\nAvailable Books:\n");
    while (fscanf(file, "%[^,],%[^\n]\n", books[count].title, books[count].author) != EOF) {
        printf("%d. %s by %s\n", count + 1, books[count].title, books[count].author);
        count++;
    }
    fclose(file);

    if (count == 0) {
        printf("No books available to update.\n");
        return;
    }

    printf("\nEnter the number of the book you want to update: ");
    if (scanf("%d", &choice) != 1 || choice < 1 || choice > count) {
        printf("Invalid choice!\n");
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

    tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error: Could not create temp file.\n");
        return;
    }

    file = fopen("books.txt", "r");
    for (i = 0; i < count; i++) {
        if (i == choice - 1) {
            fprintf(tempFile, "%s,%s\n", newTitle, newAuthor);
        } else {
            fprintf(tempFile, "%s,%s\n", books[i].title, books[i].author);
        }
    }
    fclose(file);
    fclose(tempFile);

    remove("books.txt");
    rename("temp.txt", "books.txt");

    printf("Book details updated successfully.\n");
}

// Function to set a due date for a borrowed book
void setDueDate() {
    FILE *borrowedFile, *tempFile;
    Book books[MAX_BOOKS];
    int count = 0, choice, i;
    char dueDate[11];

    borrowedFile = fopen("BorrowedBooks.txt", "r");
    if (borrowedFile == NULL) {
        printf("Error: Could not open BorrowedBooks.txt\n");
        return;
    }

    printf("\nBorrowed Books:\n");
    while (fscanf(borrowedFile, "%[^,],%[^\n]\n", books[count].title, books[count].author) != EOF) {
        printf("%d. %s by %s\n", count + 1, books[count].title, books[count].author);
        count++;
    }
    fclose(borrowedFile);

    if (count == 0) {
        printf("No borrowed books to set a due date for.\n");
        return;
    }

    printf("\nEnter the number of the book you want to set a due date for: ");
    if (scanf("%d", &choice) != 1 || choice < 1 || choice > count) {
        printf("Invalid choice!\n");
        return;
    }

    printf("\nEnter the due date (YYYY-MM-DD): ");
    getchar();
    if (fgets(dueDate, 11, stdin) == NULL) {
        printf("Error: Could not read input.\n");
        return;
    }
    dueDate[strcspn(dueDate, "\n")] = '\0';

    tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error: Could not create temp file.\n");
        return;
    }

    borrowedFile = fopen("BorrowedBooks.txt", "r");
    for (i = 0; i < count; i++) {
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
    FILE *file, *tempFile;
    Book books[MAX_BOOKS];
    int count = 0, choice, i;

    file = fopen("books.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open books.txt\n");
        return;
    }

    printf("\nAvailable Books:\n");
    while (fscanf(file, "%[^,],%[^\n]\n", books[count].title, books[count].author) != EOF) {
        printf("%d. %s by %s\n", count + 1, books[count].title, books[count].author);
        count++;
    }
    fclose(file);

    if (count == 0) {
        printf("No books available.\n");
        return;
    }

    printf("\nEnter the number of the book you want to remove: ");
    if (scanf("%d", &choice) != 1 || choice < 1 || choice > count) {
        printf("Invalid choice!\n");
        return;
    }

    tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error: Could not create temp file.\n");
        return;
    }

    file = fopen("books.txt", "r");
    for (i = 0; i < count; i++) {
        if (i != choice - 1) {
            fprintf(tempFile, "%s,%s\n", books[i].title, books[i].author);
        }
    }
    fclose(file);
    fclose(tempFile);

    remove("books.txt");
    rename("temp.txt", "books.txt");

    printf("Book removed successfully.\n");
}