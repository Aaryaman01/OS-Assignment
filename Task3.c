/* Task 3 - Secure Student Records Management System */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Maximum number of users in the system */
#define MAX_USERS 3

/* Structure to store user information and permissions */
struct User
{
    char username[30];
    char password[30];
    char role[20];

    int canCreate;
    int canWrite;
    int canRead;
    int canDelete;
    int canEncrypt;
};

/* Function to record user activities */
void writeLog(char username[], char action[], char fileName[])
{
    FILE *logFile;
    time_t currentTime;

    /* Open audit log file */
    logFile = fopen("audit_log.txt", "a");

    if(logFile == NULL)
    {
        printf("Unable to open audit log.\n");
        return;
    }

    /* Get current system time */
    time(&currentTime);

    /* Store log information */
    fprintf(logFile,
            "User: %s | Action: %s | File: %s | Time: %s",
            username,
            action,
            fileName,
            ctime(&currentTime));

    fclose(logFile);
}

/* Function to verify username and password */
int login(struct User users[], struct User *currentUser)
{
    char username[30];
    char password[30];

    printf("Login\n");

    /* Get username and password from user */
    printf("Username: ");
    scanf("%s", username);

    printf("Password: ");
    scanf("%s", password);

    /* Check entered credentials against stored users */
    for(int i = 0; i < MAX_USERS; i++)
    {
        if(strcmp(username, users[i].username) == 0 &&
           strcmp(password, users[i].password) == 0)
        {
            /* Store current logged in user */
	    *currentUser = users[i];

            printf("\nLogin Successful!\n");
            printf("Role: %s\n", currentUser->role);

	    writeLog(currentUser->username,
                     "Login Successful",
                     "System");

            return 1;
        }
    }

    /* Login failed */
    printf("\nInvalid Username or Password.\n");

    writeLog("Unknown",
             "Login Failed",
             "System");

    return 0;
}

/* Function to create a new file */
void createFile(struct User currentUser)
{
    char fileName[50];
    FILE *file;

    /* Check create permission */
    if(currentUser.canCreate == 0)
    {
        printf("Permission Denied.\n");

	writeLog(currentUser.username,
                 "Create Permission Denied",
                 "N/A");

        return;
    }

    printf("Enter file name: ");
    scanf("%s", fileName);

    /* Create file in write mode */
    file = fopen(fileName, "w");

    if(file == NULL)
    {
        printf("File creation failed.\n");
        return;
    }

    printf("File created successfully.\n");
    writeLog(currentUser.username,
         "Created File",
         fileName);

    fclose(file);
}

/* Function to write student information into a file */
void writeFile(struct User currentUser)
{
    char fileName[50];
    char text[300];

    FILE *file;

    /* Check write permission */
    if(currentUser.canWrite == 0)
    {
        printf("Permission Denied.\n");
	writeLog(currentUser.username,
             "Write Permission Denied",
             "N/A");

        return;
    }

    printf("Enter file name: ");
    scanf("%s", fileName);

    /* Open file in append mode */
    file = fopen(fileName, "a");

    if(file == NULL)
    {
        printf("File not found.\n");
        return;
    }

    getchar();

    printf("Enter student information: ");
    fgets(text, sizeof(text), stdin);

    /* Write text into file */
    fprintf(file, "%s", text);

    fclose(file);

    printf("Data written successfully.\n");
    writeLog(currentUser.username,
         "Wrote To File",
         fileName);
}

/* Function to display file contents */
void readFile(struct User currentUser)
{
    char fileName[50];
    int ch;

    FILE *file;

    /* Check read permission */
    if(currentUser.canRead == 0)
    {
        printf("Permission Denied.\n");
        writeLog(currentUser.username,
             "Read Permission Denied",
             "N/A");

	return;
    }

    printf("Enter file name: ");
    scanf("%s", fileName);

    /* Open file in read mode */
    file = fopen(fileName, "r");

    if(file == NULL)
    {
        printf("File not found.\n");
        return;
    }

    printf("\nFile Content:\n");

    /* Read file character by character */
    while((ch = fgetc(file)) != EOF)
    {
        printf("%c", ch);
    }

    printf("\n");

    fclose(file);

    writeLog(currentUser.username,
         "Read File",
         fileName);

}

/* Function to delete a file */
void deleteFile(struct User currentUser)
{
    char fileName[50];

    /* Check delete permission */
    if(currentUser.canDelete == 0)
    {
        printf("Permission Denied.\n");
        writeLog(currentUser.username,
             "Delete Permission Denied",
             "N/A");

	return;
    }

    printf("Enter file name: ");
    scanf("%s", fileName);

    /* Remove file from system */
    if(remove(fileName) == 0)
    {
        printf("File deleted successfully.\n");
        writeLog(currentUser.username,
         "Deleted File",
         fileName);
    }
    else
    {
        printf("Unable to delete file.\n");
    }
}

/* Function to encrypt or decrypt a file */
void encryptDecryptFile(struct User currentUser)
{
    FILE *file;

    char fileName[50];
    char data[1000];

    /* XOR key used for encryption and decryption */
    int key = 7;

    int i = 0;
    int ch;

    /* Check encryption permission */
    if(currentUser.canEncrypt == 0)
    {
        printf("Permission Denied.\n");
	writeLog(currentUser.username,
             "Encrypt Permission Denied",
             "N/A");

        return;
    }

    /* Get file name */
    printf("Enter file name: ");
    scanf("%s", fileName);

    /* Open file in read mode */
    file = fopen(fileName, "r");

    if(file == NULL)
    {
        printf("File not found.\n");
        return;
    }

    /* Read file and apply XOR operation */
    while((ch = fgetc(file)) != EOF && i < 999)
    {
        data[i] = ch ^ key;
        i++;
    }

    data[i] = '\0';

    fclose(file);

    /* Open file again in write mode */
    file = fopen(fileName, "w");

    if(file == NULL)
    {
        printf("Unable to save file.\n");
        return;
    }

    /* Save encrypted or decrypted data */
    fprintf(file, "%s", data);

    fclose(file);

    printf("Encryption/Decryption Completed.\n");

    writeLog(currentUser.username,
         "Encrypted/Decrypted File",
         fileName);
}

/* Main Function */
int main()
{
    /* Username, Password, Role,
   Create, Write, Read, Delete, Encrypt */

    struct User users[MAX_USERS] =
    {
        {"admin", "admin123", "Administrator",
        1,1,1,1,1},

        {"teacher", "teacher123", "Teacher",
        1,1,1,0,1},

        {"student", "student123", "Student",
        0,0,1,0,0}
    };

    struct User currentUser;

    /* Stop program if login fails */
    if(login(users, &currentUser) == 0)
    {
        return 0;
    }

    int choice;

    do
    {
        printf("\nSecure Student Records Management System\n");

        /* Display current user role */
        printf("Logged in as: %s\n", currentUser.role);

        printf("1. Create File\n");
        printf("2. Write File\n");
        printf("3. Read File\n");
        printf("4. Delete File\n");
        printf("5. Encrypt/Decrypt File\n");
        printf("6. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                createFile(currentUser);
                break;

            case 2:
                writeFile(currentUser);
                break;

            case 3:
                readFile(currentUser);
                break;

            case 4:
                deleteFile(currentUser);
                break;

    	    case 5:
    		encryptDecryptFile(currentUser);
    		break;

            case 6:
                printf("Exiting System...\n");
                break;

            default:
                printf("Invalid Choice.\n");
        }

    } while(choice != 6);

    return 0;
}
