/*
============================================================================
Name : 16writelck.c
Author : Tarun Sharma
Description : A program to perform mandatory locking.
Date: 25th Aug, 2023.
============================================================================
*/
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

int main(void){
        struct flock lock;
        int fd = open("criticalsectionfile",O_RDWR);
        lock.l_type=F_WRLCK;
        lock.l_whence=SEEK_SET;
        lock.l_start=0;
        lock.l_len=0;
        lock.l_pid=getpid();
        printf("Section before entering into critical section\n");
        fcntl(fd,F_SETLKW,&lock);
        printf("Inside the critical section.....\n");
        printf("Enter to unlock\n");
        getchar();
        printf("Unlocked\n");
        lock.l_type=F_UNLCK;
        fcntl(fd,F_SETLK,&lock);
        printf("FIN\n");
}

