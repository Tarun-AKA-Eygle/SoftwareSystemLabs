/*
============================================================================
Name : 18.c
Author : Tarun Sharma
Description : A program to find out total number of directories on the pwd. execute ls -l | grep ^d | wc ? Use only dup2.
Date: 5th Sep, 2023.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
        dup2(pipefd[0], STDIN_FILENO);

        // Execute 'wc'
        execlp("wc", "wc", NULL);

        // If execlp fails
        perror("execlp");
        exit(EXIT_FAILURE);
    } else { // Parent process
	int pfd[2];
	if (pipe(pfd) == -1) {
	         perror("pipe");
          exit(EXIT_FAILURE);
      }
	pid_t ch_pid = fork();
	
	if(ch_pid == 0){
	        close(pipefd[0]); // Close the read end of the pipe
		close(pfd[1]);//close the write end of pipe
		dup2(pfd[0],STDIN_FILENO);		
		dup2(pipefd[1],STDOUT_FILENO);
		execlp("grep","grep ^d",NULL);
		perror("execlp");
		exit(EXIT_FAILURE);
		
}
	else{

        	close(pfd[0]);

		// Redirect the standard output to write to the pipe
	      
		dup2(pfd[1],STDOUT_FILENO);
        	// Execute 'ls -l'
        	execlp("ls", "ls", "-l", NULL);

	        // If execlp fails
	        perror("execlp");
	        exit(EXIT_FAILURE);
	}
    }

    return 0;
}

