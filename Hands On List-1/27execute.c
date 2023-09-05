#include <unistd.h>
#include <stdio.h>
int main(void){
	char *const envp[2] = {"STEPLIB=SASC.V6.LINKLIB", NULL};	
        execlp("ls","ls","-l","-R",(char*) NULL);
	execl("/usr/bin/ls","ls","-R",(char*) NULL);
	execle("/usr/bin/ls","ls","-R",(char*) NULL,envp);
	char *arg[5];
	arg[0]="ls";
	arg[1]="-l";
	arg[2]="-R";
	arg[3]=NULL;
	execv("/usr/bin/ls",arg);
	execvp("/usr/bin/ls",arg);
	

}
