#include <stdio.h>
#include <stdlib.h>
#include "library.h"



void displayMenu() {
    printf("\nSAINT LOUIS UNIVERSITY LIBRARY SYSTEM:\n");
    printf("----------------------------------------\n");
    printf("1. Borrow a Book\n");
    printf("2. Return a Book\n");
    printf("3. Donate a Book\n");
    printf("4. Search for a Book\n");
    printf("5. List All Books\n");
    printf("6. Update Book Details\n");
    printf("7. Set Due Date for a Book\n");
    printf("8. Remove a Book\n");
    printf("9. Exit\n");
    printf("----------------------------------------\n");
}

int main() {
    int choice;

    while (1) {
        displayMenu();
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1 || choice < 1 || choice > 9) {
            printf("Invalid input. Please enter a number between 1 and 9.\n");
            while (getchar() != '\n'); // Clear invalid input
            continue;
        }

        switch (choice) {
            case 1: borrowBook(); break;
            case 2: returnBook(); break;
            case 3: donateBook(); break;
            case 4: searchBook(); break;
            case 5: listBooks(); break;
            case 6: updateBookDetails(); break;
            case 7: setDueDate(); break;
            case 8: removeBook(); break;
            case 9: 
                printf("Exiting program.\n");
                exit(0);
            default: 
                printf("Invalid choice, please try again.\n");
        }
    }

    return 0;
}

