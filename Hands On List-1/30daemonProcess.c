#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void){
	if(!fork()){
		setsid();// set this process as session leader
		chdir("/"); // change directory of this process to root
		umask(0);  // permission in reverse order
		while(1){
			// Specify the time like sleep(2);
			sleep(10);
			printf("Return child process id %d\n",getpid());
			printf("Daemon process is running ......\n");
		}
	}
	else
		exit(0);
}
// ps -el | grep <cpid>
