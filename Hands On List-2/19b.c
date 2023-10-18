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

