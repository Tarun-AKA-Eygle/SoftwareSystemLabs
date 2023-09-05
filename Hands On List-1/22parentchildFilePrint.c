#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc,char* argv[]){
	if(argc!=2){
		printf("Please enter correct arguments");
		return 0;
	}
	int fd_write = open(argv[1],O_WRONLY|O_CREAT,0744);
	if(fd_write==-1)
			printf("Error");
	if(fork()){
		char bufi[11]="I am Parent";
		//printf("Enter things parent process want to add\n");
		//scanf(" %[^\n]", bufi);
		int char_write = write(fd_write,&bufi,11);
		 int fd_write_close = close(fd_write);
                if(fd_write_close==-1)
                        printf("Error");
	}
	else{
		char bufi[10]="I am Child";
		//printf("Enter things child process want to add\n");
		//scanf(" %[^\n]", bufi);
		int char_write = write(fd_write,&bufi,10);
		int fd_write_close = close(fd_write);
		if(fd_write_close==-1)
                        printf("Error");
	}
	return 0;
}
