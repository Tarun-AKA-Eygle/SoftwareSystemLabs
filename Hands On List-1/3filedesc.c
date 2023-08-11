#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
int main(){
	int crt = creat("tempcreatefile1",O_CREAT);
	printf("%d",crt);
	return 0;
}
