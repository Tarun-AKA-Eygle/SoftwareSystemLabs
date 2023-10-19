/*
============================================================================
Name : 23.c
Author : Tarun Sharma
Description : A program to print the maximum number of files can be opened within a process and size of a pipe.
Date: 5th Sep, 2023.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>
int main() 
{
    struct rlimit fileLimit;
    if(getrlimit(RLIMIT_NOFILE, &fileLimit) == 0) 
    {
        printf("Maximum number of files that can be opened: %lu\n", fileLimit.rlim_cur);
    } 
    int pipe_fd[2];
    int pipeSize = fpathconf(pipe_fd[0], _PC_PIPE_BUF);
    printf("Size of a pipe (circular buffer): %d bytes\n", pipeSize);
    return 0;
}

