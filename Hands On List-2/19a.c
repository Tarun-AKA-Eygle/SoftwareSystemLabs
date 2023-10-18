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

