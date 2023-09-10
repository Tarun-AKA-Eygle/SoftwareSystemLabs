/*
============================================================================
Name : 27execute.c
Author : Tarun Sharma
Description : A program to execute ls -Rl.
Date: 5th Sep, 2023.
============================================================================
*/
#include <unistd.h>
#include <stdio.h>
int main(void){
//      execlp("ls","ls","-l","-R",(char*) NULL);
//	execl("/usr/bin/ls","ls","-R",(char*) NULL);
	execle("/usr/bin/ls","ls","-R",(char*) NULL,NULL);
	char *arg[5];
	arg[0]="ls";
	arg[1]="-l";
	arg[2]="-R";
	arg[3]=NULL;
//	execv("/usr/bin/ls",arg);
//	execvp("/usr/bin/ls",arg);
	

}
