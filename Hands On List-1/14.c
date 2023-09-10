/*
============================================================================
Name : 14.c
Author : Tarun Sharma
Description : A program to find the type of a file.
Date: 22th Aug, 2023.
============================================================================
*/
#include <sys/types.h>
       #include <sys/stat.h>
       #include <stdint.h>
       #include <time.h>
       #include <stdio.h>
       #include <stdlib.h>
       #include <sys/sysmacros.h>

int main(int argv,char* argc[]){
	if(argv!=2)
		return 0;
	struct stat s;
	stat (argc[1],&s);
	printf("File type: ");
	// /dev -> directory
	if(S_ISBLK(s.st_mode))
		printf("block device\n");
	else
	if(S_ISCHR(s.st_mode))
		printf("character device\n");
	else
	if(S_ISDIR(s.st_mode))
		printf("directory\n");
	else
	if(S_ISFIFO(s.st_mode))
		printf("FIFO/pipe\n");
	else
	if(S_ISLNK(s.st_mode))
		printf("symlink\n");
	else
	if(S_ISSOCK(s.st_mode))
		printf("socket\n");
	else
	if(S_ISREG(s.st_mode))
                printf("REgular file\n");
	else
		printf("unknown?\n");
	return 0;
}
