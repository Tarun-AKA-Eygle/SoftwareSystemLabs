#include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
int main(int argc,char* argv[]){
	if(argc!=2){	
		printf("Please enter correct arguments");
		return 0;
	}
	int fd_read = open(argv[1],O_RDONLY);
	if(fd_read==-1 )
			printf("Error");
	int comparisionValue = 10; // ASCII Value \n
	int lineNO = 1;
	printf("%d ",lineNO);
	while(1){
		char buf;
		int char_read = read(fd_read,&buf,1);
		if(char_read==0)
			break;
		if(buf==comparisionValue)
		{ printf("\n");
			lineNO++;
			printf("%d ",lineNO);

		}
		else
			printf("%c",buf);

	}
	int fd_read_close = close(fd_read);
	if(fd_read_close==-1)
                        printf("Error");
	return 0;
}
