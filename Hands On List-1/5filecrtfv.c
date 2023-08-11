#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
int main(){
	int crt = creat("file1",O_CREAT);
	crt = creat("file2",O_CREAT);
	crt = creat("file3",O_CREAT);
	crt = creat("file4",O_CREAT);
	crt = creat("file5",O_CREAT);
	while(1);
	return 0;
}
