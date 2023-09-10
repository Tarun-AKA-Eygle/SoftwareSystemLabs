/*
============================================================================
Name : 9.c
Author : Tarun Sharma
Description : A program to print the information about a given file.
Date: 22th Aug, 2023.
============================================================================
*/
#include <sys/types.h>
       #include <sys/stat.h>
       #include <stdint.h>
       #include <time.h>
       #include <stdio.h>
       #include <stdlib.h>
       #include <sys/sysmacros.h>

int main(int argv,char* argc[]){
	if(argv!=2)
		return 0;
	struct stat s;
	struct timespec t;
	stat (argc[2],&s);
	printf("Inode no. %ld\n",s.st_ino);
	printf("No. of hard links %ld\n",s.st_nlink);
	printf("UID %u\n",s.st_uid);
	printf("GID %u\n",s.st_gid);
	printf("File size %ld\n",s.st_size);
	printf("No. of blocks %ld\n",s.st_blocks);
	printf("Time of last access %s\n", ctime(&s.st_atime));
	printf("Time of last modification %s\n",ctime(&s.st_mtime));
	printf("Time of last change %s\n",ctime(&s.st_ctime));
	return 0;		
}
