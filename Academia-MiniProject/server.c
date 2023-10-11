#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define MAX_CLIENTS 5
#define BUFFER_SIZE 1024
#define PORT 8081 

void *handle_client(void *arg);

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    pthread_t tid[MAX_CLIENTS];

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket creation error");
        exit(1);
    }

    // Initialize server address structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);  // Port number
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket to address
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Bind error");
        exit(1);
    }

    // Listen for incoming connections
    if (listen(server_socket, MAX_CLIENTS) == -1) {
        perror("Listen error");
        exit(1);
    }

    printf("Server listening on port \n");

    int i = 0;

    while (1) {
        // Accept a new client connection
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_socket == -1) {
            perror("Accept error");
            continue;
        }

        // Create a new thread to handle the client
        if (pthread_create(&tid[i], NULL, handle_client, &client_socket) != 0) {
            perror("Thread creation error");
            continue;
        }

        i = (i + 1) % MAX_CLIENTS;
    }

    close(server_socket);
    return 0;
}

void *handle_client(void *arg) {
    int client_socket = *((int *)arg);
    char buffer[BUFFER_SIZE];
    ssize_t bytes_received;
    int choice;
    char login[BUFFER_SIZE];
    char pass[BUFFER_SIZE];
    // Read and echo data from the client
    bytes_received = recv(client_socket, &choice, sizeof(choice), 0);

    bytes_received = recv(client_socket, login, sizeof(login), 0);

    bytes_received = recv(client_socket, pass, sizeof(pass), 0);

    // Do authentication will take (ch,login,password)

    // if Authentication successful
    // Client will open appropriate menu item
    
    // char msg[BUFFER_SIZE];
    // snprintf(msg, sizeof(msg), "%d", choice);
    send(client_socket, &choice, sizeof(choice), 0);
    
    close(client_socket);
    pthread_exit(NULL);
}

