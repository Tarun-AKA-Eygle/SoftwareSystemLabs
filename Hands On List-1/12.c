 #include <sys/types.h>

#include <unistd.h>

#include <fcntl.h>

#include <stdio.h>
int main(int argv,char* argc[]){
	if(argv!=2){
		return 0;
	}
	int fd1 = open(argc[1],O_CREAT|O_RDWR,0744);
	if(fd1==-1)
		printf("Error");
	int c = fcntl(fd1,F_GETFL,O_ACCMODE);
	printf("%d",c);
	return 0;
}
/*
*** Flag                       O_RDONLY =     0 =            0 = x0000
*** Flag                       O_WRONLY =     1 =            1 = x0001
*** Flag                         O_RDWR =     2 =           10 = x0002
*** Flag                        O_CREAT =    64 =      1000000 = x0040
*** Flag                        O_TRUNC =   512 =   1000000000 = x0200
*** Flag                       O_APPEND =  1024 =  10000000000 = x0400
*** Flag   O_WRONLY | O_CREAT | O_TRUNC =   577 =   1001000001 = x0241
*** Flag  O_WRONLY | O_CREAT | O_APPEND =  1089 =  10001000001 = x0441
*** Flag     O_RDWR | O_CREAT | O_TRUNC =   578 =   1001000010 = x0242
*** Flag    O_RDWR | O_CREAT | O_APPEND =  1090 =  10001000010 = x0442
*** Mode  r  F_GETFL -> 32768 = 1000000000000000 = x8000
*** Mode  w  F_GETFL -> 32769 = 1000000000000001 = x8001
*** Mode  a  F_GETFL -> 33793 = 1000010000000001 = x8401
*** Mode r+  F_GETFL -> 32770 = 1000000000000010 = x8002
*** Mode w+  F_GETFL -> 32770 = 1000000000000010 = x8002
*** Mode a+  F_GETFL -> 33794 = 1000010000000010 = x8402
*/
