/*
============================================================================
Name : 19b.c
Author : Tarun Sharma
Description : A program create a FIFO file by a. mknod system call b. mkfifo library function
Date: 5th Sep, 2023.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
int main() 
{
    mkfifo("mkfifoFIFOfile", 0666);
    printf("FIFO file \"%s\" created successfully.\n", "mkfifoFIFOfile");
    return 0;
}

