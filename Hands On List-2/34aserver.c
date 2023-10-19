/*
============================================================================
Name : 34aserver.c
Author : Tarun Sharma
Description : a program to create a concurrent server.
Date: 5th Sep, 2023.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#define PORT 8080
#define MAX_CLIENTS 5

void handle_client(int client_socket) {
    char buffer[1024];
    int bytes_received;

    while (1) {
        memset(buffer, 0, sizeof(buffer));
        bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_received <= 0) {
            // Client closed the connection or an error occurred.
            break;
        }

        printf("Received: %s", buffer);

        // Echo the received data back to the client.
        send(client_socket, buffer, bytes_received, 0);
    }

    // Close the client socket.
    close(client_socket);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    pid_t child_pid;

    // Create a socket.
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket creation error");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the specified address and port.
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Binding error");
        close(server_socket);
        exit(1);
    }

    // Start listening for incoming connections.
    if (listen(server_socket, MAX_CLIENTS) == -1) {
        perror("Listening error");
        close(server_socket);
        exit(1);
    }

    printf("Server is listening on port %d...\n", PORT);

    while (1) {
        // Accept a client connection.
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
        if (client_socket == -1) {
            perror("Accept error");
            continue;
        }

        // Fork a new process to handle the client.
        if ((child_pid = fork()) == 0) {
            // This is the child process.
            close(server_socket); // Close the server socket in the child process.
            handle_client(client_socket); // Handle the client.
            exit(0); // Exit the child process.
        } else if (child_pid < 0) {
            perror("Fork error");
        }

        // In the parent process, close the client socket.
        close(client_socket);
    }

    // Close the server socket.
    close(server_socket);

    return 0;
}

