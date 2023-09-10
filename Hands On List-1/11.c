/*
============================================================================
Name : 11.c
Author : Tarun Sharma
Description : A program to open a file, duplicate the file descriptor and append the file with both the descriptors.
Date: 22th Aug, 2023.
============================================================================
*/
#include <fcntl.h>              /* Obtain O_* constant definitions */
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main(int argv,char* argc[]){
	if(argv!=2){
		return 0;
	}
	int fd1 = open(argc[1],O_CREAT|O_RDWR|O_APPEND,0744);
	if(fd1==-1)
		printf("Error");
	int fd2 = dup(fd1);
	char str[] = "File Descriptor of primary fd is \0";
	int appendFileDescp = write(fd1,&str,sizeof(str));
	char fd[3];
	sprintf(fd,"%d\n",fd1);
	int appendFileDescpfd = write(fd1,&fd,sizeof(fd));
	char str1[] = "File Descriptor of duplicate fd is \0";
        appendFileDescp = write(fd1,&str1,sizeof(str1));
        sprintf(fd,"%d\n",fd2);
	appendFileDescpfd = write(fd1,&fd,sizeof(fd));
	int fd3;
       	dup2(fd2,fd3);
	char str2[] = "File Descriptor of dup2 fd is \0";
        appendFileDescp = write(fd1,&str2,sizeof(str2));
        sprintf(fd,"%d\n",fd3);
        appendFileDescpfd = write(fd1,&fd,sizeof(fd));
	int fd4 = fcntl(fd1,F_DUPFD);
	char str3[] = "File Descriptor of fcntl fd is \0";
        appendFileDescp = write(fd1,&str3,sizeof(str3));
        sprintf(fd,"%d\n",fd4);
        appendFileDescpfd = write(fd1,&fd,sizeof(fd));
	int fd_read = open(argc[1],O_RDONLY,0744);
	while(1){
		char buf;
		int char_read = read(fd_read,&buf,1);
		if(char_read==0)
			break;
		printf("%c",buf);
	}
	return 0;
}
