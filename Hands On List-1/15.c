/*
============================================================================
Name : 15.c
Author : Tarun Sharma
Description : A program to display the environmental variable of the user.
Date: 22th Aug, 2023.
============================================================================
*/
#include <unistd.h>
#include <stdio.h>

extern char **environ;

int main(void){
	int i = 0;
	while(environ[i]) {
	  printf("%s\n", environ[i++]); // prints in form of "variable=value"
	}	
}
