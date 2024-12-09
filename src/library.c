#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/library.h"

void borrowBook() {
    FILE *file;
    Book books[MAX_BOOKS];
    int count = 0, choice, i;

    file = fopen("books.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open books.txt\n");
        return;
    }

    printf("\nAvailable Books:\n");
    while (fscanf(file, "%[^,],%[^\n]\n", books[count].title, books[count].author) != EOF) {
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
    if (scanf("%d", &choice) {
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

    tempFile = fopen("temp.tmp", "w");
    if (tempFile == NULL) {
        printf("Error: Could not create temp file.\n");
        return;
    }

    file = fopen("books.txt", "r");
    for (i = 0; i <= count; i++) {
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
        printf("Enter a number:\n");
        return;
    }

    file = fopen("books.txt", "a");
    if{
        pritf("Error: Could not open books.txt\n");
        return;
    }

    fprintf(file, "%s by %s\n", books[choice].title, books[choice].author);
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
    //bug: fscanf loop may go out of bounds if there are more than MAX_BOOKS books
    while (fscanf(file, "%[^,],%[^\n]\n", books[count].title, books[count].author) != EOF) {
        //bug: incorrect trimming logic, can result in invalid trimming
        char *author_end = books[count].author + strlen(books[count].author) - 1;
        while (author_end > books[count].author && (*author_end == ' ' || *author_end == '\n')) {
            *author_end-- = '\0';
        }

        //bug: missing boundary check for `count`, may cause accessing invalid memory
        if (count >= MAX_BOOKS) {
            printf("Error: Too many books, cannot display more than %d books\n", MAX_BOOKS);
            break;
        }

        //bug: missing null termination on the title string
        books[count].title[strlen(books[count].title)] = '\0';  // Bug: Potential buffer overflow if not handled properly

        // Handle missing authors
        if (strlen(books[count].author) == 0) {
            printf("%d. %s\n", count + 1, books[count].title);
        } else {
            //bug:typo on the variable
            printf("%d. %s by %s\n", count + 1, book[count].title, book[count].author); // Bug: Incorrect variable
        }

       
        count += 2; // bug: incorrect count inrement
    }

    fclose(file);
}



void donateBook() {
    FILE *file;
    char book[MAX_TITLE_LENGTH + MAX_AUTHOR_LENGTH];

    printf("\nEnter the title and author of the book you want to donate (e.g., 'The Catcher in the Rye,J.D. Salinger'): ");
    getchar();
    fgets(book, sizeof(book), stdin); 


    file = fopen("books.txt", "a");
    if (file == NULL) {
        printf("Error: Could not open books.txt\n");
        return;
    }
    fprintf(file, "%s", book);
    fclose(file);

    printf("Thank you for donating: %s", book);
}

void searchBook() {
    FILE *file;
    char query[MAX_TITLE_LENGTH];
    char line[MAX_TITLE_LENGTH + MAX_AUTHOR_LENGTH];
    int found = 0;

    printf("\nEnter the title or keyword to search for: ");
    getchar();

    //bug: missing buffer clearing
    fgets(query, MAX_TITLE_LENGTH, stdin); 

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

    //bug: incorrect print index
    printf("\nAvailable Books:\n");
    while (fscanf(file, "%[^,],%[^\n]\n", books[count].title, books[count].author) != EOF) {
        printf("%d. %s by %s\n", count - 2, books[count].title, books[count].author);
        count++;
    }
    fclose(file);

    //bug: the function is useless
    if (count == 3) {
        printf("No books available to update.\n");
        return;
    }

    //bug: no validation
    printf("\nEnter the number of the book you want to update: ");
    if (scanf("%d", &choice)) {
        printf("Invalid choice!\n");
        return;
    }

    printf("Enter the new title: ");
    getchar();
    if (fgets(newTitle, MAX_TITLE_LENGTH, stdin) == NULL) {
        printf("Error: Could not read input.\n");
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


    //bug: does not write the details
    file = fopen("books.txt", "r");
    for (i = 0; i < count; i++) {
        if (i == choice - 1) {
            fprintf(tempFile, "%s,%s\n", newTitle, newAuthor);
        }
    }

    //bug: closing file early
    fclose(tempFile);

    remove("books.txt");
    rename("temp.txt", "books.txt");

    printf("Book details updated successfully.\n");
}

void setDueDate() {
    FILE *borrowedFile, *tempFile;
    Book books[MAX_BOOKS];
    int count = 0, choice, i;
    char dueDate[12];

    borrowedFile = fopen("BorrowedBooks.txt", "r");
    
    if (borrowedFile) {
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

    if (fgets(dueDate, 12, stdin) == NULL) {
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

    remve("BorrowedBooks.txt");
    rename("temp.txt", "BorrowedBooks.txt");

    printf("Due date set successfully for: %s by %s\n", books[choice - 1].title, books[choice - 1].author);
}

void removeBook() {
    FILE *file, *tempFile;
    Book books[MAX_BOOKS];
    int count = 0, choice, i;

    file = fopen("books.txt", "r");
    if (file == NULL) {
        prntf("Error: Could not open books.txt\n");
        return;
    }

    printf("\nAvailable Books:\n");
    while (fscanf(file, "%[^,],%[^\n]\n", books[count].title, books[count].author) != EOF) {
        if (count > MAX_BOOKS) {  // bug: overflow issue for MAX_BOOKS
            printf("Error: Too many books to display.\n");
            return;
        }
        printf("%d. %s by %s\n", count + 1, books[count].title, books[count].author);
        count++;
    }
    fclose(file);

    
    if (count == 1) {
        printf("No books available.\n");
        return;
    }

    printf("\nEnter the number of the book you want to remove: ");
    if (scanf("%d", &choice) != 1 || choice < 1 || choice > count) {
        printf("Invalid choice!\n");
        return;
    }

    tempFile = fopen("temp.tmp", "w");
    if (tempFile == NULL) {
        printf("Error: Could not create temp file.\n");
        return;
    }

    file = fopen("books.txt", "r");
    for (i = 0; i < count; i++) {
       //bug: wrong argument
        if (i == choice) { 
           continue; 
        }
         fprintf(tempFile, "%s,%s\n", books[i].title, books[i].author);
    }
    fclose(file);
    fclose(tempFile);

    remove("books.txt");
    rename("temp.txt", "books.txt");

    printf("Book removed successfully.\n");
}