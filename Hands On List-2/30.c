#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
int main() {
    key_t key;
    int shmid;
    char *shared_memory;
    key = ftok(".", 'D');
    shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    shared_memory = shmat(shmid, NULL, 0);
    const char *data_to_write = "Original Data";
    strncpy(shared_memory, data_to_write, 1024);
    printf("Data written to shared memory: %s\n", data_to_write);
    return 0;
}

