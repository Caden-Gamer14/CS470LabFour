#include "libFS2025.h"

// Global variables
FileEntry file_table[MAX_FILES];  // File table to track files
int file_count = 0;               // Number of files in the system

// Create a new file
int fileCreate(const char *filename) {

    // Check if file already exists
    for (int i = 0; i < file_count; i++) {
        if (strcmp(file_table[i].filename, filename) == 0) {
            printf("Error: File '%s' already exists.\n", filename);
            return -1;
        }
    }

    // Create the file on the local disk
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error: Unable to create file '%s'.\n", filename);
        return -1;
    }
    fclose(file);

    // Add file to the file table
    strcpy(file_table[file_count].filename, filename);
    file_table[file_count].size = 0;
    file_table[file_count].is_open = 0;  // File is closed
    file_count++;

    printf("File '%s' created successfully.\n", filename);
    return 0;
}

// Open a file
int fileOpen(const char *filename) {
    for (int i = 0; i < file_count; i++) {
        if (strcmp(file_table[i].filename, filename) == 0) {
            if (file_table[i].is_open) {
                printf("Error: File '%s' is already open.\n", filename);
                return -1;
            }
            file_table[i].is_open = 1;  // Mark file as open
            printf("File '%s' opened successfully.\n", filename);
            return i;  // Return file index
        }
    }

    printf("Error: File '%s' not found.\n", filename);
    return -1;
}

// Write data to a file
int fileWrite(int file_index, const char *data) {

    if (!file_table[file_index].is_open) {
        printf("Error: File '%s' is not open.\n", file_table[file_index].filename);
        return -1;
    }

    int data_size = strlen(data);

    // Write data to the local file
    FILE *file = fopen(file_table[file_index].filename, "w");
    if (!file) {
        printf("Error: Unable to open file '%s' for writing.\n", file_table[file_index].filename);
        return -1;
    }
    fwrite(data, 1, data_size, file);
    fclose(file);

    file_table[file_index].size = data_size;
    printf("Data written to file '%s' successfully.\n", file_table[file_index].filename);
    return 0;
}

// Read data from a file
int fileRead(int file_index, char *buffer, int buffer_size) {

    //Creates an if statement for determining if a file is not open 
    if (!file_table[file_index].is_open) {

        printf("Error: File '%s' is not open.\n", file_table[file_index].filename); 

        return -1; 

    }

    //Uses the fopen method to read the data from the local file in the designated area 
    FILE *file = fopen(file_table[file_index].filename, "r"); 

    //Creates an if statement if there are any errors when opening the file 
    if (!file) {

        printf("Error: Unable to open file '%s' for reading.\n", file_table[file_index].filename); 

        return -1; 

    }

    fread(buffer, 1, buffer_size, file); 

    //Closes the file using fclose 
    fclose(file);

    //Final printf statement for output 
    printf("Data read from file '%s' successfully.\n", file_table[file_index].filename); 

    return 0;

}


// Close a file
int fileClose(int file_index) {

    //Creates an if statement for if the file is not open 
    if (file_index < 0 || file_index >= file_count || !file_table[file_index].is_open) {

        printf("Error: File is not open.\n"); 

        return -1; 
        
    }

    //Uses the file_table to make sure the file is closed 
    file_table[file_index].is_open = 0; 

    //Final printf statement for closing the file 
    printf("File '%s' closed successfully.\n", file_table[file_index].filename); 

    return 0;

}


// Delete a file
int fileDelete(const char *filename) {

    //Creates a for loop to go through and see if the file is opened 
    for (int i = 0; i < file_count; i++) {

        //If statement for determining if the file is open 
        if (strcmp(file_table[i].filename, filename) == 0) {

            if (file_table[i].is_open) {

                //Printf statement for output 
                printf("Error: Cannot delete an open file.\n"); 

                return -1; 

            }

            //Uses the remove method to delete the file 
            remove(filename); 

            //Uses file_table to remove the file table 
            file_table[i] = file_table[--file_count]; 

            //Uses the printf to give a final printf method 
            printf("File '%s' deleted successfully.\n", filename); 

            return 0;

        }
    }

    //Uses the printf method to give a final output 
    printf("Error: File '%s' not found.\n", filename); 

    return -1;

}