/*
============================================================================
Name : 6.c
Author : Tarun Sharma
Description : A program to take input from STDIN and display on STDOUT using read/write system calls.
Date: 22th Aug, 2023.
============================================================================
*/
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main(void){
	int fd1,fd2,i;
	char bufi[1024];
	printf("Enter the a line\n");
        scanf(" %[^\n]", bufi);
	fd1 = open("filefor6", O_WRONLY,0777);
 	write(fd1,bufi,1024);
	fd2 = open("filefor6", O_RDONLY,0777);
	i = read(fd2,bufi,sizeof(bufi));
	printf("%s",bufi);
	close(fd1);
	close(fd2);
}
