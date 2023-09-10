/*
============================================================================
Name : 5filecrtfv.c
Author : Tarun Sharma
Description : A program to create five new files with infinite loop and execute the program in the background and check the file descriptor table at /proc/pid/fd.
Date: 12th Aug, 2023.
============================================================================
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
int main(){
	int crt = creat("file1",O_CREAT);
	crt = creat("file2",O_CREAT);
	crt = creat("file3",O_CREAT);
	crt = creat("file4",O_CREAT);
	crt = creat("file5",O_CREAT);
	while(1);
	return 0;
}
