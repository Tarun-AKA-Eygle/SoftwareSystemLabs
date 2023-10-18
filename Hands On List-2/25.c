#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <time.h>
int main() {
    key_t key;
    int msgid;
    key = ftok(".", 'B');
    msgid = msgget(key, 0666 | IPC_CREAT);
    struct msqid_ds msq_info;
    msgctl(msgid, IPC_STAT, &msq_info);
    printf("a. Access permission: %#o\n", msq_info.msg_perm.mode);
    printf("b. UID: %d, GID: %d\n", msq_info.msg_perm.uid, msq_info.msg_perm.gid);
    printf("c. Time of last message sent: %s", ctime(&msq_info.msg_stime));
    printf("d. Time of last message received: %s", ctime(&msq_info.msg_rtime));
    printf("e. Time of last change in the message queue: %s", ctime(&msq_info.msg_ctime));
    printf("f. Size of the queue: %lu bytes\n", (unsigned long)msq_info.msg_qbytes);
    printf("g. Number of messages in the queue: %lu\n", (unsigned long)msq_info.msg_qnum);
    printf("h. Maximum number of bytes allowed: %lu bytes\n", (unsigned long)msq_info.msg_qbytes);
    printf("i. PID of msgsnd: %d\n", msq_info.msg_lspid);
    printf("j. PID of msgrcv: %d\n", msq_info.msg_lrpid);
    return 0;
}

