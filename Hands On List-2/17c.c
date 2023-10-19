/*
============================================================================
Name : 17c.c
Author : Tarun Sharma
Description : A program to execute ls -l | wc. a. use dup b. use dup2 c. use fcntl
Date: 5th Sep, 2023.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h> 
#include <sys/types.h>
int main() {
    int pipefd[2];
    pid_t child_pid;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) { // Child process
        close(pipefd[1]); // Close the write end of the pipe

        // Redirect the standard input to read from the pipe
//	close(0);
	fcntl(pipefd[0],F_DUPFD, STDIN_FILENO);
        // Execute 'wc'
        execlp("wc", "wc", NULL);

        // If execlp fails
        perror("execlp");
        exit(EXIT_FAILURE);
    } else { // Parent process
        close(pipefd[0]); // Close the read end of the pipe

        // Redirect the standard output to write to the pipe
//	close(1);
	fcntl(pipefd[1],F_DUPFD, STDOUT_FILENO);
        // Execute 'ls -l'
        execlp("ls", "ls", "-l", NULL);

        // If execlp fails
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    return 0;
}

