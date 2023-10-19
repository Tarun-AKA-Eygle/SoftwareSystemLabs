/*
============================================================================
Name : 33client.c
Author : Tarun Sharma
Description : a program to communicate between two machines using socket.
Date: 5th Sep, 2023.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1" // Change to the server's IP address
#define PORT 12345
#define MAX_BUFFER_SIZE 1024

int main() {
    int client_socket;
    struct sockaddr_in server_address;

    // Create socket
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Prepare the server address structure
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Connect to the server
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    char message[MAX_BUFFER_SIZE];
    while (1) {
        // Input a message to send to the server
        printf("Enter a message (or 'exit' to quit): ");
        fgets(message, sizeof(message), stdin);

        // Send the message to the server
        send(client_socket, message, strlen(message), 0);

        // Receive and print the server's response
        char buffer[MAX_BUFFER_SIZE];
        ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_received <= 0) {
            perror("Server disconnected");
            break;
        }
        buffer[bytes_received] = '\0';
        printf("Server response: %s\n", buffer);

        // Check if the client wants to exit
        if (strcmp(message, "exit\n") == 0) {
            break;
        }
    }

    // Close the socket
    close(client_socket);

    return 0;
}

