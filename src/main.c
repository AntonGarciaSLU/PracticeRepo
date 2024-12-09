#include <stdio.h>
#include <stdlib.h>
#include "../include/library.h"


int main() {
    int choice;

    while (1) {
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
        printf("Enter your choice: ");
        scanf("%d", &choice); 
        
        switch (choice) {
            case 1:
                borrowBook(1); 
            break;
            case 2:
                return_Book(); 
            break;
            case 3:
                donateBook("Hello"); 
            break;
            case 4:
            
            break;
            case 5:
                listBooks();
                giveDetails(); 
            break;
            case 6:
                updateBookDetails();
            break;
            case 7:
                setDueDateForBook(); 
            break;
            cse 8: 
                removeBook();
            break;
            case 9:
                printf("Exiting program.\n");
            exit(0);
            default:
                printf("Goodbye!.\n"); 
        }
    }

    return 0;
}
