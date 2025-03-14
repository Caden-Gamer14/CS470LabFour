#include "Caden_libFS2025.h"
#include <ctype.h>  // For tolower()

// Function to display the menu
void displayMenu() {
    printf("\n--- Menu ---\n");
    printf("1. Create a file\n");
    printf("2. Open a file\n");
    printf("3. Write to a file\n");
    printf("4. Read from a file\n");
    printf("5. Close a file\n");
    printf("6. Delete a file\n");
    printf("7. Exit\n");
    printf("Enter your choice: ");
}

// Function to wait for user input to continue
void waitForUser() {
    printf("\nPress Enter to continue...");
    getchar();  // Wait for Enter key
    getchar();  // Clear the newline character from the buffer
}

int main() {
    char filename[MAX_FILENAME];
    char introduction[] = "Hello, my name is Caden\n\n"
                          "I love frogs because frog spelled backwards is gorf.\n"
                          "Minecraft is awesome and can have shakespearian writing.\n"
                          "I also like saying Hey D00d and Jolly Good Show Indeed!!";
    int file_index = -1;  // Track the currently open file
    int choice;
    char buffer[MAX_FILE_SIZE];

    while (1) {
        displayMenu();
        scanf("%d", &choice);  // Get user choice
        getchar();  // Clear the newline character from the buffer

        switch (choice) {
            case 1:  // Create a file
                printf("Enter the filename to create: ");
                fgets(filename, MAX_FILENAME, stdin);
                filename[strcspn(filename, "\n")] = '\0';  // Remove newline
                if (fileCreate(filename) != 0) {
                    printf("Error creating file.\n");
                }
                waitForUser();
                break;

            case 2:  // Open a file
                printf("Enter the filename to open: ");
                fgets(filename, MAX_FILENAME, stdin);
                filename[strcspn(filename, "\n")] = '\0';  // Remove newline
                file_index = fileOpen(filename);
                if (file_index == -1) {
                    printf("Error opening file.\n");
                }
                waitForUser();
                break;

            case 3:  // Write to a file
                if (file_index == -1) {
                    printf("Error: No file is open. Please open a file first.\n");
                } else {
                    printf("Writing introduction to file '%s'...\n", filename);
                    if (fileWrite(file_index, introduction) != 0) {
                        printf("Error writing to file.\n");
                    }
                }
                waitForUser();
                break;

            case 4:  // Read from a file 
                
                //Creates an if statement to determine if a file is open or not 
                if (file_index == -1) {

                    printf("Error: No file is open. Please open a file first.\n"); 
                
                //Creates an else statement to determine what happens when you read from a file
                } else { 

                    //If statement for if the file is sucessfully read 
                    if (fileRead(file_index, buffer, sizeof(buffer)) == 0) {

                        printf("Contents of '%s':\n%s\n", filename, buffer);

                    //Else statement if there is an error 
                    } else {

                        printf("Error reading from file.\n"); 

                    }
                }

                waitForUser();

                break;

            case 5: // Close a file 

                //Creates an if statement to close the file 
                if (file_index != -1) {

                    fileClose(file_index); 

                    //Assigns file_index to -1 to reset the index of the file 
                    file_index = -1; 

                //Creates an else statement if no file is available to be opened 
                } else {

                    printf("Error: No file is open.\n"); 

                }
                waitForUser(); 
                break;

            case 6: // Delete a file 
                
                //Creates a printf statement for user instructions 
                printf("Enter the file name to delete: "); 
    
                fgets(filename, MAX_FILENAME, stdin); 
                
                //Removes the line created 
                filename[strcspn(filename, "\n")] = '\0'; 
    
                //Creates an if statement if there are any issues with deleting the file 
                if (fileDelete(filename) != 0) {
    
                    printf("Error deleting file.\n"); 
    
                }
                
                waitForUser(); 

                break; 

            case 7:  // Exit
                printf("Exiting the program. Goodbye!\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
                waitForUser();
                break;
        }
    }

    return 0;
}