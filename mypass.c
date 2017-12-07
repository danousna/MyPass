/*
Project :       MyPass
Description :   MyPass is a password manager app.
                Command line interface version of the app.
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

void encryptData(char * password) {

    // Calling openssl
    char command[300] = "openssl enc -aes-256-cbc -salt -in ";
    strcat(command, FILE_NAME);
    strcat(command, " -out ");
    strcat(command, ENC_FILE_NAME);
    strcat(command, " -k ");
    strcat(command, password);
    system(command);

    memset(command, 0, strlen(command));

    strcpy(command, "rm ");
    strcat(command, FILE_NAME);
    system(command);
}

void decryptData(char * password) {

    // Calling openssl
    char command[300] = "openssl enc -aes-256-cbc -d -in ";
    strcat(command, ENC_FILE_NAME);
    strcat(command, " -out ");
    strcat(command, FILE_NAME);
    strcat(command, " -k ");
    strcat(command, password);
    system(command);

    memset(command, 0, strlen(command));

    strcpy(command, "rm ");
    strcat(command, ENC_FILE_NAME);
    system(command);

}

int fileExist(char * opt) {
    if (!strcmp(opt, "d")) {
        if (access(FILE_NAME, F_OK) != -1) {
            printf("\nA MyPass file has been detected in this directory.\n\n");
            return 1;
        } else {
            printf("\nNo MyPass file has been detected in this directory.\n\n");
            return 0;
        }
    } else if (!strcmp(opt, "e")) {
        if (access(ENC_FILE_NAME, F_OK) != -1) {
            printf("\nA MyPass file has been detected in this directory.\n\n");
            return 1;
        } else {
            printf("\nNo MyPass file has been detected in this directory.\n\n");
            return 0;
        }
    } else {
        perror("Cannot detect option");
    }
}

void reset() {

    // *** Checking if file exists ***
    int continueReset = fileExist("d");

    if (continueReset) {

        // *** Confirm reset ***

        char resetConfirm = '\0';
        printf("Are you sure you want to delete your mypass file ? (Y/n)\n");
        scanf(" %c", &resetConfirm);

        char command[30] = "rm ";

        switch (resetConfirm) {
            case 'Y':
                strcat(command, FILE_NAME);
                system(command);
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
    printf("\nInitialisation of mypass file...\n");


    // *** Checking if file exists ***
    int continueInit = fileExist("d");

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
            encryptData(password);
            printf("\nMypass has been setup, you can now add accounts with the -add option\n\n");
        } else {
            printf("\nError: The two passwords don't match\n\n");
        }
    } else {
        char resetConfirm = '\0';
        printf("Do you wish to reset ? (This will delete the detected mypass file) (Y/n)\n");
        scanf(" %c", &resetConfirm);
        switch (resetConfirm) {
            case 'Y':
                reset();
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

void add() {

    // *** Checking if encrypted file exists ***
    int encFileDetected = fileExist("e");
    int decFileDetected = fileExist("d");

    char password[60];
    char * ptr;

    ptr = getpass("Master password: ");
    strcpy(password, ptr);
    memset(ptr, 0, strlen(ptr));

    if (encFileDetected) {

        // *** Decrypting the file ***
        decryptData(password);

        // *** Prompting user for informations ***
        account tmp;

        printf("Name: ");
        scanf("%s", tmp.name);
        printf("User: ");
        scanf("%s", tmp.user);
        printf("Password: ");
        scanf("%s", tmp.password);


        char data[250];

        long int id = time(NULL);
        char * id_str = malloc(15);
        // Convert long to str.
        sprintf(id_str, "%li", id);

        strcat(data, "\n");
        strcat(data, id_str);
        strcat(data, "(");
        strcat(data, tmp.name);
        strcat(data, ",");
        strcat(data, tmp.user);
        strcat(data, ",");
        strcat(data, tmp.password);
        strcat(data, ")");

        writeFile(FILE_NAME, data, "a+");

        encryptData(password);

        printf("\nAccount added with the following informations :\n");
        printf("%s\n", data);
    } else if (decFileDetected) {
        encryptData(password);
    }
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
                decryptData("Natan");
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
