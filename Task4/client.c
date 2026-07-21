/*
    Task 4 - Network Programming & IPC
    Scenario: Secure Student Chat System

    Concepts:
    - socket()
    - connect()
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
    int clientSocket;

    struct sockaddr_in serverAddress;

    /* Create socket */
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (clientSocket < 0)
    {
        printf("Socket creation failed.\n");
        return 1;
    }

    printf("Client socket created successfully.\n");

    /* Configure server address */
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);

    /* Server IP Address */
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    /* Connect to server */
    if (connect(clientSocket,
                (struct sockaddr *)&serverAddress,
                sizeof(serverAddress)) < 0)
    {
        printf("Connection failed.\n");
        close(clientSocket);
        return 1;
    }

    printf("Connected to server successfully.\n");

    close(clientSocket);

    return 0;
}
