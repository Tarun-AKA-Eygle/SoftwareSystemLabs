/*
============================================================================
Name : 27b.c
Author : Tarun Sharma
Description : A program to receive messages from the message queue. a. with 0 as a flag b. with IPC_NOWAIT as a flag
Date: 5th Sep, 2023.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
struct msg_buffer {
    long msg_type;
    char msg_text[512];
};
int main() {
    key_t key;
    int msgid;
    struct msg_buffer message;
    key = ftok(".", 'B');
    msgid = msgget(key, 0666);
    while (1) {
        ssize_t result = msgrcv(msgid, (void*)&message, 512, 0, IPC_NOWAIT);
        if (result == -1) {
                break;
            }
        printf("Received Message Type: %ld\n", message.msg_type);
        printf("Message Text: %s\n", message.msg_text);
        printf("----------------------------\n");
    }

    return 0;
}

