#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
int main() 
{
    int fd;
    fd = open("21fifo", O_RDWR|O_CREAT, 0777);
    char message[] = "Hello from Writer!";
    write(fd, message, sizeof(message));
    char response[100];
    ssize_t bytesRead = read(fd, response, sizeof(response));
    if (bytesRead > 0) 
    {
        response[bytesRead] = '\0';  // Null-terminate the string
        printf("Received response: %s\n", response);
    }
    close(fd);
    return 0;
}

