#include <sched.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

struct sched_param p;

int main(void){
	p.sched_priority = 10;
	switch(sched_getscheduler(getpid()))
	{
		case SCHED_RR:
			printf("Current policy is RR\n");
			break;
		case SCHED_FIFO:
			printf("Current policy is FIFO\n");
			break;
		case SCHED_OTHER:
			printf("Current policy is others\n");
			break;
		default:
			printf("Error\n");
	}
	int ch=-1;
	while(ch==-1){
		printf("Press 1 to change the scheduler to round robin\nPress 2 to change the scheduler to fifo\nPress 3 to change the scheduler to others\n");
		scanf("%d",&ch);
		if(ch<1 || ch >3) ch=-1;
	}
	if(ch==1)
		sched_setscheduler(getpid(),SCHED_RR,&p);
	if(ch==2)
		sched_setscheduler(getpid(),SCHED_FIFO,&p);
	if(ch==3)
		sched_setscheduler(getpid(),SCHED_OTHER,&p);	
	switch(sched_getscheduler(getpid()))
	{
		case SCHED_RR:
			printf("Current policy is RR\n");
			break;
		case SCHED_FIFO:
			printf("Current policy is FIFO\n");
			break;
		case SCHED_OTHER:
			printf("Current policy is others\n");
			break;
		default:
			printf("Error\n");
	}
}
