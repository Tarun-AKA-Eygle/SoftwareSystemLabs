#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(){
	int op = open("tempcreatefile1",O_CREAT|O_EXCL);
	printf("%d",op);
	return 0;
}
