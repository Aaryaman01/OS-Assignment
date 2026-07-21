/*
    Task 4 - Network Programming & IPC
    Scenario: Secure Student Chat System

    Concepts:
    - socket()
    - bind()
    - listen()
    - accept()
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>

#define PORT 8080

/* User structure */
struct User
{
    char username[30];
    char password[30];
};

/* Valid users */
struct User users[3] =
{
    {"admin", "admin123"},
    {"teacher", "teacher123"},
    {"student", "student123"}
};

/* Function to handle each client */
void *handleClient(void *arg)
{
    int clientSocket = *((int *)arg);

    char buffer[1024];

    memset(buffer, 0, sizeof(buffer));

    int bytesReceived;

    bytesReceived = recv(clientSocket,
                     buffer,
                     sizeof(buffer),
                     0);

    /* Client disconnected */
    if (bytesReceived <= 0)
    {
    	printf("Client disconnected.\n");

    	close(clientSocket);

    	pthread_exit(NULL);
    }

    /* Empty message */
    if (strlen(buffer) == 0)
    {
    	send(clientSocket,
             "EMPTY_MESSAGE",
             13,
             0);

    	close(clientSocket);

    	pthread_exit(NULL);
    }

    printf("\nReceived: %s\n", buffer);

    char command[20];
    char username[30];
    char password[30];

    int fields;

    fields = sscanf(buffer,
                "%s %s %s",
                command,
                username,
                password);

    if (fields != 3)
    {
        send(clientSocket,
       	    "INVALID_FORMAT",
            14,
            0);

    	printf("Invalid login format.\n");

    	close(clientSocket);

    	pthread_exit(NULL);
    }

    if (strcmp(command, "LOGIN") != 0)
    {
    	send(clientSocket,
             "INVALID_COMMAND",
             15,
             0);

    	printf("Invalid command.\n");

    	close(clientSocket);

    	pthread_exit(NULL);
    }

    int authenticated = 0;

    for (int i = 0; i < 3; i++)
    {
        if (strcmp(username, users[i].username) == 0 &&
            strcmp(password, users[i].password) == 0)
        {
            authenticated = 1;
            break;
        }
    }

    if (authenticated)
    {
        send(clientSocket, "AUTH_SUCCESS", 12, 0);
        printf("Authentication successful.\n");
    }
    else
    {
        send(clientSocket, "AUTH_FAILED", 11, 0);
        printf("Authentication failed.\n");
    }

    close(clientSocket);

    pthread_exit(NULL);
}

int main()
{
    int serverSocket;
    int clientSocket;

    struct sockaddr_in serverAddress;
    struct sockaddr_in clientAddress;

    socklen_t clientLength;

    pthread_t thread;

    /* Create socket */
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    /* Allow port reuse */
    int opt = 1;

    setsockopt(serverSocket,
               SOL_SOCKET,
               SO_REUSEADDR,
               &opt,
               sizeof(opt));

    if (serverSocket < 0)
    {
        printf("Socket creation failed.\n");
        return 1;
    }

    printf("Server socket created successfully.\n");

    /* Configure server address */
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(PORT);

    /* Bind socket */
    if (bind(serverSocket,
             (struct sockaddr *)&serverAddress,
             sizeof(serverAddress)) < 0)
    {
        printf("Bind failed.\n");
        close(serverSocket);
        return 1;
    }

    printf("Server bound to port %d.\n", PORT);

    /* Listen for clients */
    if(listen(serverSocket, 5)< 0)
    {
	printf("Listen failed.\n");
	close(serverSocket);
	return 1;
    }

    printf("Server listening\n");

    /* Keep server running */
    while (1)
    {
        int clientSocket;

        clientLength = sizeof(clientAddress);

        clientSocket = accept(serverSocket,
                              (struct sockaddr *)&clientAddress,
                              &clientLength);

        if (clientSocket < 0)
        {
            printf("Accept failed.\n");
            continue;
        }

        printf("Client connected.\n");

        pthread_t thread;

        pthread_create(&thread,
                       NULL,
                       handleClient,
                       &clientSocket);

        pthread_detach(thread);
    }

    close(serverSocket);

    return 0;
}
