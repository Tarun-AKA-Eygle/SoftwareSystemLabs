#include<stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

struct value{
	int data;
}db;

int main(void){
	int input;
	printf("Select the record number\n");
	scanf("%d",&input);
	struct flock lock;
	int fd = open("recordlockfile",O_RDWR);
	lock.l_type=F_WRLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=((input-1)*sizeof(db),SEEK_SET);
	lock.l_len=sizeof(db);
	lock.l_pid=getpid();
	printf("Section before entering into critical section\n");
	fcntl(fd,F_SETLKW,&lock);
	printf("Inside the critical section.....\n");
	struct value currRecord;
	int bytesread = read(fd,&currRecord,sizeof(currRecord));
	if(bytesread==-1){
		currRecord.data=0;
	}
	printf("Your Previous Value was %d",currRecord.data++);
	lseek(fd,-1*sizeof(db),SEEK_CUR);
	write(fd,&currRecord,sizeof(currRecord));
	printf("Enter to unlock\n");
	getchar();
	getchar();
	printf("Unlocked\n");
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	printf("FIN\n");
}

