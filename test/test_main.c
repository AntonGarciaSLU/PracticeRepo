#include <stdio.h>
#include <stdlib.h>
#include "../include/library.h"

// Function to display a test menu for direct testing
void displayTestMenu() {
    printf("\nSAINT LOUIS UNIVERSITY LIBRARY SYSTEM - TEST MENU:\n");
    printf("----------------------------------------\n");
    printf("1. Test Borrow Book\n");
    printf("2. Test Return Book\n");
    printf("3. Test Donate Book\n");
    printf("4. Test Search Book\n");
    printf("5. Test List Books\n");
    printf("6. Test Update Book Details\n");
    printf("7. Test Set Due Date\n");
    printf("8. Test Remove Book\n");
    printf("9. Exit\n");
    printf("----------------------------------------\n");
}

int main() {
    int choice;

    do {
        displayTestMenu();
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please try again.\n");
            while (getchar() != '\n'); // Clear invalid input
            continue;
        }

        switch (choice) {
            case 1:
                printf("\nTesting Borrow Book...\n");
                borrowBook();
                break;
            case 2:
                printf("\nTesting Return Book...\n");
                returnBook();
                break;
            case 3:
                printf("\nTesting Donate Book...\n");
                donateBook();
                break;
            case 4:
                printf("\nTesting Search Book...\n");
                searchBook();
                break;
            case 5:
                printf("\nTesting List Books...\n");
                listBooks();
                break;
            case 6:
                printf("\nTesting Update Book Details...\n");
                updateBookDetails();
                break;
            case 7:
                printf("\nTesting Set Due Date...\n");
                setDueDate();
                break;
            case 8:
                printf("\nTesting Remove Book...\n");
                removeBook();
                break;
            case 9:
                printf("\nExiting Test Program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 9);

    return 0;
}
