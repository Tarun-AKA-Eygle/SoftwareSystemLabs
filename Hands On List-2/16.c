/*
============================================================================
Name : 16.c
Author : Tarun Sharma
Description : A program to send and receive data from parent to child vice versa. Use two way communication.
Date: 5th Sep, 2023.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int parent_to_child_pipe[2]; // Pipe for parent to child communication
    int child_to_parent_pipe[2]; // Pipe for child to parent communication

    if (pipe(parent_to_child_pipe) == -1 || pipe(child_to_parent_pipe) == -1) {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Child process
        close(parent_to_child_pipe[1]); // Close the write end of the parent-to-child pipe
        close(child_to_parent_pipe[0]); // Close the read end of the child-to-parent pipe

        char message_from_parent[100];
        char message_to_parent[100];

        while (1) {
            // Child receives message from parent
            read(parent_to_child_pipe[0], message_from_parent, sizeof(message_from_parent));
            printf("Child received: %s\n", message_from_parent);

            // Child sends a message to parent
            printf("Enter a message for parent: ");
            fgets(message_to_parent, sizeof(message_to_parent), stdin);
            write(child_to_parent_pipe[1], message_to_parent, strlen(message_to_parent) + 1);
        }

        close(parent_to_child_pipe[0]);
        close(child_to_parent_pipe[1]);
    } else { // Parent process
        close(parent_to_child_pipe[0]); // Close the read end of the parent-to-child pipe
        close(child_to_parent_pipe[1]); // Close the write end of the child-to-parent pipe

        char message_to_child[100];
        char message_from_child[100];

        while (1) {
            // Parent sends a message to child
            printf("Enter a message for child: ");
            fgets(message_to_child, sizeof(message_to_child), stdin);
            write(parent_to_child_pipe[1], message_to_child, strlen(message_to_child) + 1);

            // Parent receives message from child
            read(child_to_parent_pipe[0], message_from_child, sizeof(message_from_child));
            printf("Parent received: %s\n", message_from_child);
        }

        close(parent_to_child_pipe[1]);
        close(child_to_parent_pipe[0]);
    }

    return 0;
}

