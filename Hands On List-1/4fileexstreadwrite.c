/*
============================================================================
Name : 4fileexstreadwrite.c
Author : Tarun Sharma
Description : A program to open an existing file with read write mode.
Date: 12th Aug, 2023.
============================================================================
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(){
	int op = open("tempcreatefile1",O_CREAT|O_EXCL);
	printf("%d",op);
	return 0;
}
