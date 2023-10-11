#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "mainMenu.h"
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8081
#define BUFFER_SIZE 1024

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_received;
    ssize_t bytes_read;
    // Create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Socket creation error");
        exit(1);
    }

    // Initialize server address structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Connect to server
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection error");
        exit(1);
    }
    menu();
    // Send data to the server
        int choice;
        bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer));

        if (bytes_read == -1) {
            perror("read");
            return 1;
        }

        // Null-terminate the string
        buffer[bytes_read] = '\0';

        // Convert the string to an integer using atoi
        choice = atoi(buffer);
        send(client_socket, &choice, sizeof(choice), 0);
        
        login();
        fgets(buffer, sizeof(buffer), stdin);
        send(client_socket, buffer, strlen(buffer), 0);

        password();
        fgets(buffer, sizeof(buffer), stdin);
        send(client_socket, buffer, strlen(buffer), 0);


        char str[]="Login Successful!\n";
	    write(STDOUT_FILENO,str,strlen(str));

        
        bytes_received = recv(client_socket, &choice, sizeof(choice), 0);

        switch (choice)
        {
        case 1:
            admin();

            break;
        case 2:
            break;
        case 3:
            break;
        default:
            break;
        }
    

    close(client_socket);
    return 0;
}
