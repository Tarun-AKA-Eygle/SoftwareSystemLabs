#include<stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(){
	struct{
		int ticket_no;
	}db;
	struct flock lock;
	int fd = open("criticalsectionfile",O_WRONLY);
	lock.l_type=F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=0;
	lock.l_len=0;
	lock.l_pid=getpid();
	printf("Before entering into critical section\n");
	fcntl(fd,F_SETLKW,&lock);
	printf("Inside the critical section.....\n");
	printf("Enter the ticket no ");
	scanf("%d",&db.ticket_no);
	write(fd,&db,sizeof(db));
	printf("Enter to unlock\n");
	getchar();
	printf("Unlocked\n");
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	printf("FIN\n");
}
