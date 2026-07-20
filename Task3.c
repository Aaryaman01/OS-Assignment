/* Task 3 - Secure Student Records Management System */

#include <stdio.h>
#include <stdlib.h>

void createFile()
{
    char fileName[50];
    FILE *file;

    printf("Enter file name: ");
    scanf("%s", fileName);

    file = fopen(fileName, "w");

    if(file == NULL)
    {
        printf("File creation failed.\n");
        return;
    }

    printf("File created successfully.\n");

    fclose(file);
}

void writeFile()
{
    char fileName[50];
    char text[300];

    FILE *file;

    printf("Enter file name: ");
    scanf("%s", fileName);

    file = fopen(fileName, "a");

    if(file == NULL)
    {
        printf("File not found.\n");
        return;
    }

    getchar();

    printf("Enter student information: ");
    fgets(text, sizeof(text), stdin);

    fprintf(file, "%s", text);

    fclose(file);

    printf("Data written successfully.\n");
}

void readFile()
{
    char fileName[50];
    int ch;

    FILE *file;

    printf("Enter file name: ");
    scanf("%s", fileName);

    file = fopen(fileName, "r");

    if(file == NULL)
    {
        printf("File not found.\n");
        return;
    }

    printf("\nFile Content:\n");

    while((ch = fgetc(file)) != EOF)
    {
        printf("%c", ch);
    }

    printf("\n");

    fclose(file);
}

void deleteFile()
{
    char fileName[50];

    printf("Enter file name: ");
    scanf("%s", fileName);

    if(remove(fileName) == 0)
    {
        printf("File deleted successfully.\n");
    }
    else
    {
        printf("Unable to delete file.\n");
    }
}

int main()
{
    int choice;

    do
    {
        printf("\nSecure Student Records Management System\n");
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
                createFile();
                break;

            case 2:
                writeFile();
                break;

            case 3:
                readFile();
                break;

            case 4:
                deleteFile();
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
