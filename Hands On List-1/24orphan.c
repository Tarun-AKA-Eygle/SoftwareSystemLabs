/*
============================================================================
Name : 24orphan.c
Author : Tarun Sharma
Description : A program to create an orphan process.
Date: 5th Sep, 2023.
============================================================================
*/
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <time.h>
#include <stdlib.h>
int main(){
	// Command to see orphan process -> ps aux | grep returned value
	int pid = fork();
	if(pid){
		printf("This is a parent process and the child's process id is %d\n",pid);
	}
	else{
		sleep(1000);
		printf("This is a child process\n");

	}
	return 0;
}

