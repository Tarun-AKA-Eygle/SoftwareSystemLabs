#include<stdio.h>
#include <stdlib.h>
#include <string.h>

void menu(){
	char str[]=".....................Welcome To Academia :: Course Registration..................\nLoginType\nEnter Your Choice {1. Admin, 2. Professor, 3.Student} : \n";
	write(STDOUT_FILENO,str,strlen(str));
	
}

void login(){
	char str[]="Enter Login-ID : ";
	write(STDOUT_FILENO,str,strlen(str));
}

void password(){
	char str[]="Enter Password : ";
	write(STDOUT_FILENO,str,strlen(str));
}


void admin(){

	char str[]=".....................Welcome To Admin Menu..................\n1. Add Student\n2. View Student Details\n3. Add Faculty\n4. View Faculty Details\n5. Activate Student\n6. Block Student\n7. Modify Student Details\n8. Modify Faculty Details\n9. Logout and Exit\nEnter Your Choice: ";
	write(STDOUT_FILENO,str,strlen(str));
	

}