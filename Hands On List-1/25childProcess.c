#include <sys/wait.h>
#include <stdint.h>
#include <stdlib.h>
       #include <unistd.h>
       #include <stdio.h>
void main(){
	int ch=-1;
	while(ch==-1){
		printf("Choose out of 3 which child process should parent process wait\n");
		scanf("%d",&ch);
		if(ch<1 && ch >3) ch =-1;
	}
	int wstatus;
	int p1=fork();
	int p2=fork();
	int p3=fork(),cpid;
	if(ch==1) cpid=p1;
	if(ch==2) cpid=p2;
	if(ch==3) cpid=p3;
	if(p1==0 && p2!=0 && p3!=0) printf("First child executed\n");
        if(p2==0 && p1!=0 && p3!=0) printf("Second child executed\n");
	if(p3==0 && p1!=0 && p2!=0) printf("Third child executed\n");	
	if(p1!=0 && p2!=0 && p3!=0){
		pid_t w = waitpid(cpid, &wstatus,WUNTRACED | WCONTINUED);
		if (w == -1) {
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
		printf("Parent Executed\n");
	}
	
}
		
