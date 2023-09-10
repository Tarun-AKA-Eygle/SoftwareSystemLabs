/*
============================================================================
Name : 10.c
Author : Tarun Sharma
Description : A program to open a file with read write mode, write 10 bytes, move the file pointer by 10 bytes (use lseek) and write again 10 bytes.
Date: 22th Aug, 2023.
============================================================================
*/
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc,char* argv[]){
	if(argc !=2)
		return 0;
	int fd_rdwt = open(argv[1],O_CREAT|O_RDWR,0744);
	if(fd_rdwt==-1)
		printf("Error\n");
	char bufi[10];
	printf("Enter things you want to add\n");
	scanf(" %[^\n]", bufi);
	int char_write = write(fd_rdwt,&bufi,10);
	int seek = lseek(fd_rdwt,10,SEEK_CUR);
	printf("Value returned by lseek %d\n",seek);
	printf("Enter things you want to add\n");
        scanf(" %[^\n]", bufi);
        int char_write_again = write(fd_rdwt,&bufi,10);

	return 0;	
}
