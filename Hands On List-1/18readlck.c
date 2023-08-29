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
	lock.l_type=F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=((input-1)*sizeof(db),SEEK_SET);
	lock.l_len=sizeof(db);
	lock.l_pid=getpid();
	printf("Section before entering into critical section\n");
	fcntl(fd,F_SETLKW,&lock);
	printf("Inside the critical section.....\n");
	//db.data++;
	//lseek(fd,-1*sizeof(db),SEEK_CUR);
	struct value currRecord;
	read(fd,&currRecord,sizeof(currRecord));
	printf("Your Value is %d",currRecord.data);
	printf("Enter to unlock\n");
	getchar();
	printf("Unlocked\n");
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	printf("FIN\n");
}

