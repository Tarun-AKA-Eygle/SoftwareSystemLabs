#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(){
	struct {
		int ticket_no;
	}db;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start=0;
	lock.l_len=0;
	lock.l_pid=getpid();
	printf("Before entering into critical section\n");
	int fd = open("criticalsectionfile",O_RDWR);
	fcntl(fd,F_SETLKW,&lock);
	read(fd,&db,sizeof(db));
	printf("Current ticket number: %d\n",db.ticket_no++);
	lseek(fd,0L,SEEK_SET);
	printf("Inside the critical section..\n");
	printf("Enter to unlock..\n");
	write(fd,&db,sizeof(db));
	getchar();
	lock.l_type=F_UNLCK;
	printf("Unlocked\n");
	fcntl(fd,F_SETLK,&lock);
	printf("Finish\n");
	close(fd);
	return 0;
}
