#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
int main() 
{
    int fd;
    mkfifo("21fifo", 0666);
    fd = open("21fifo", O_RDWR);
    char buffer[100];
    ssize_t bytesRead = read(fd, buffer, sizeof(buffer));
    if (bytesRead > 0) 
    {
        buffer[bytesRead] = '\0';  // Null-terminate the string
        printf("Received message: %s\n", buffer);
        char response[] = "Message received!";
        write(fd, response, sizeof(response));
    }
    close(fd);
    unlink("21fifo");
    return 0;
}

