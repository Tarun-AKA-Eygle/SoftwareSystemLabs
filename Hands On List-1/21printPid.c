#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void){
	if(!fork()){
	printf("Process id of child %ld\n",(long)getpid());
	}
	else
	printf("Process id of parent %ld\n",(long)getpid());
		
}
