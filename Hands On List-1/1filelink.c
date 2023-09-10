/*
============================================================================
Name : 1filelink.c
Author : Tarun Sharma
Description : System call to create soft link,hard link,FIFO.
Date: 28th Aug, 2023.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(){
	int v = symlink("systemcallfile","softlnkfile");
	if(v<0)
		{perror("Failed"); return 1;}
	int f = link("systemcallfile","hrdlnkfile");
	if(f<0)
		{perror("Failed"); return 1;}
	int e = mknod("fifocallfile",S_IFIFO,0);
	if(e<0)
		perror("Failed");	
	return 0;
}
