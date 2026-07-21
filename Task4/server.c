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

#define PORT 8080

int main()
{
    int serverSocket;
    int clientSocket;

    struct sockaddr_in serverAddress;
    struct sockaddr_in clientAddress;

    socklen_t clientLength;

    /* Create socket */
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

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
    if (listen(serverSocket, 5) < 0)
    {
        printf("Listen failed.\n");
        close(serverSocket);
        return 1;
    }

    printf("Server listening...\n");

    /* Accept client */
    clientLength = sizeof(clientAddress);

    clientSocket = accept(serverSocket,
                          (struct sockaddr *)&clientAddress,
                          &clientLength);

    if (clientSocket < 0)
    {
        printf("Accept failed.\n");
        close(serverSocket);
        return 1;
    }

    printf("Client connected successfully.\n");

    /* Close sockets */
    close(clientSocket);
    close(serverSocket);

    return 0;
}
