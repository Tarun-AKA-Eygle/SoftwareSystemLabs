/*
============================================================================
Name : 21printPid.c
Author : Tarun Sharma
Description : A program, call fork and print the parent and child process id.
Date: 5th Sep, 2023.
============================================================================
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void){
	if(!fork()){
	printf("Process id of child %ld\n",(long)getpid());
	}
	else
	printf("Process id of parent %ld\n",(long)getpid());
		
}
