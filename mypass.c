/*
Project :       MyPass
Description :   MyPass is a password manager app. 
                This is the command line interface version of the app.
Author :        Natan Danous
Date created :  22/11/2017
Version :       0.0.1
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

// Globals
#define FILE_NAME ".data.mypass"
#define ENC_FILE_NAME ".enc_data.mypass"

// Structs
typedef struct {
    char name[60];
    char user[60];
    char password[60];
} account;

void writeFile(char * fileName, char * data, char * opt) {
    FILE *data_file = fopen(fileName, opt);
    fputs(data, data_file);
    fclose(data_file);

    printf("Wrote to %s\n\n", fileName);
}

void readFile(char * fileName) {
    char * buffer = 0;
    long length;
    FILE *data_file = fopen(fileName, "r");

    if (data_file) {
        fseek(data_file, 0, SEEK_END);
        length = ftell(data_file);
        fseek(data_file, 0, SEEK_SET);
        buffer = malloc(length);
        if (buffer) {
            fread(buffer, 1, length, data_file);
        }
        fclose(data_file);
    }

    if (buffer) {
        printf("%s\n", buffer);
    }
}

int fileExist() {
    if (access(FILE_NAME, F_OK) != -1) {
        printf("\nA MyPass file has been detected in this directory.\n");
        return 1;
    } else {
        printf("\nNo MyPass file has been detected in this directory.\n");
        return 0;
    }
}

void reset() {

    // *** Checking if file exists ***
    int continueReset = fileExist();

    if (continueReset) {

        // *** Confirm reset ***

        char resetConfirm = '\0';
        printf("Are you sure you want to delete your mypass file ? (Y/n)\n");
        scanf(" %c", &resetConfirm);

        switch (resetConfirm) {
            case 'Y':
                printf("File has been deleted\n");
                break;
            case 'n':
                printf("Reset aborted\n");
                break;
            default:
                printf("Error: Reset aborted, please retry.\n");
                break;
        }
    }
}

void initialise() {

    // *** Init screen ***
    printf("\nInitialisation of mypass file...\n\n");


    // *** Checking if file exists ***
    int continueInit = fileExist();

    if (!continueInit) {
    
        // *** Writing a header to data file (code is messy) ***
        
        char headerStart[] = "//MyPass data file\n//Timestamp : ";
        char * time_str = malloc(15);
        long int time_long = time(NULL);
        
        // Here 19 is approximate of length of time_long (+1 for \0).
        int length = strlen(headerStart) + 20;
        char * header = malloc(length);
        
        // Convert long to str.
        sprintf(time_str, "%li", time_long);
        
        // Make the header proper.
        strcpy(header, headerStart);
        strcat(header, time_str);
        
        // Write to file.
        writeFile(FILE_NAME, header, "w+");

        // Free memory.
        free(header);


        // *** Ask for password and encrypt the file ***

        char password[60], passwordConfirm[60];
        char * ptr;
        
        ptr = getpass("Enter a master password: ");
        strcpy(password, ptr);

        ptr = getpass("Confirm your master password: ");
        strcpy(passwordConfirm, ptr);

        memset(ptr, 0, strlen(ptr));
                
        if (!strcmp(password, passwordConfirm)) {
            printf("Password entry successful\n");
        } else {
            printf("\nError: The two passwords don't match\n\n");
        }
    }
}

void add() {

    // *** Checking if file exists ***
    int continueAdd = fileExist();

    if (continueAdd) {

        // *** Prompting user for informations ***
        account tmp; 

        printf("Name: ");
        scanf("%s", tmp.name);
        printf("User: ");
        scanf("%s", tmp.user);
        printf("Password: ");
        scanf("%s", tmp.password);


        char data[200];
        strcat(data, "\n\n");
        strcpy(data, tmp.name);
        strcat(data, "\n");
        writeFile(FILE_NAME, data, "a+");

        printf("\nAccount added with the following informations :\n");
        printf("%s\n", data);
    }
}

void encrypt() {

}

void decrypt() {

}

int main(int argc, char *argv[]) {
    switch(argc) {
        case 1:
            printf("\nError: no arguments given, try 'mypass -help'\n\n");
            break;
        case 2:
            // Main for single argument
            if (!strcmp(argv[1], "-init")) {
                initialise();
            } 
            else if (!strcmp(argv[1], "-reset")) {
                reset();
            }
            else if (!strcmp(argv[1], "-test")) {
                printf("\nTest ok\n\n");
            }
            else if (!strcmp(argv[1], "-add")) {
                add();
            }
            else if (!strcmp(argv[1], "-list")) {
                //list();
            } 
            else {
                printf("\nError: argument not recognized, try 'mypass -help'\n\n");
            }
            break;
        case 3:  
            // Main for two arguments          
            break;
    }
    return 0;
}