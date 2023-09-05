#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <time.h>
// command to see zombie process-> ps aux | grep Z
int main(){
	if(fork()){
		printf("This is a parent process\n");
		sleep(1000);
	}
	else{
		printf("This is a child process\n");

	}
	return 0;
}
