/*
============================================================================
Name : 3filedesc.c
Author : Tarun Sharma
Description : A program to create a file and print the file descriptor value.
Date: 12th Aug, 2023.
============================================================================
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
int main(){
	int crt = creat("tempcreatefile1",O_CREAT);
	printf("%d",crt);
	return 0;
}
