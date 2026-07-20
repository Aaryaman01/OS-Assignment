/* Task 3 - Secure Student Records Management System */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

            return 1;
        }
    }

    /* Login failed */
    printf("\nInvalid Username or Password.\n");

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
}

/* Function to delete a file */
void deleteFile(struct User currentUser)
{
    char fileName[50];

    /* Check delete permission */
    if(currentUser.canDelete == 0)
    {
        printf("Permission Denied.\n");
        return;
    }

    printf("Enter file name: ");
    scanf("%s", fileName);

    /* Remove file from system */
    if(remove(fileName) == 0)
    {
        printf("File deleted successfully.\n");
    }
    else
    {
        printf("Unable to delete file.\n");
    }
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
        printf("5. Exit\n");

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
                printf("Exiting System...\n");
                break;

            default:
                printf("Invalid Choice.\n");
        }

    } while(choice != 5);

    return 0;
}
