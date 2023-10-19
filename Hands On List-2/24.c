/*
============================================================================
Name : 24.c
Author : Tarun Sharma
Description : A program to create a message queue and print the key and message queue id.
Date: 5th Sep, 2023.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
int main() 
{
    key_t key;
    int msgid;
    key = ftok(".", 'B');
    msgid = msgget(key, 0666 | IPC_CREAT);
    printf("Key: %x\n", (unsigned int)key);
    printf("Message Queue ID: %d\n", msgid);
    return 0;
}

