#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>
int main(){
	int curPri = getpriority(PRIO_PROCESS,0);
	printf("Current process priority is %d",curPri);
	int inc;
	scanf("%d",&inc);
	int newPri = nice(inc);
	printf("New process priority is %d",newPri);
	return 0;
}
