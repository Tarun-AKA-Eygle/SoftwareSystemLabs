/*
============================================================================
Name : 19a.c
Author : Tarun Sharma
Description : A program create a FIFO file by a. mknod system call b. mkfifo library function
Date: 5th Sep, 2023.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int main() 
{
    mknod("mknodFIFOfile", S_IFIFO | 0666, 0); 
    printf("FIFO file '%s' created successfully.\n", "mknodFIFOfile");
    return 0;
}

