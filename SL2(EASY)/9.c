#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<unistd.h>
#include<string.h>

int main()
{


int choice;
int fd;
int rd;
char filename[20];
char buff[BUFSIZ];
char* temp[BUFSIZ];
char ch;
do
{
printf("\nMENU:\n1)Create/Open file\n2)Read from file\n3)Write to file\n4)Close file\n5)Exit\n");
printf("enter choice");
scanf("%d",&choice);

switch(choice)
{
	case 1:
	printf("Enter the name of the file you want to create\n");
	scanf("%s",filename);
	fd=open(filename,O_CREAT | O_RDWR);
	if(fd!=-1)
	printf("File successfully created");
	else
	printf("Error occured while creating file\n");
	break;

	case 2:
	fd=open(filename,O_RDONLY);
	rd=read(fd,temp,BUFSIZ);
	printf("File after reading is :%s",temp);
	
	if(rd==-1)
	printf("error\n");
	break;
	
	case 3:
	printf("Enter Student name\t");
	scanf("%c",&ch);
	scanf("%[^\n]s",buff);
	write(fd,buff,strlen(buff));
	//write(fd,"\t",strlen(buff));
	
	printf("Enter Student Subject\t");
	scanf("%c",&ch);
	scanf("%[^\n]s",buff);
	write(fd,buff,strlen(buff));
	//write(fd,"\t",strlen(buff));
	
	printf("Enter Student Marks\n");
	scanf("%c",&ch);
	scanf("%[^\n]s",buff);
	write(fd,buff,strlen(buff));
	//write(fd,"\t",strlen(buff));
	break;
	
	case 4:
	close(fd);
	printf("File closed successfully\n");
	break;
	
	case 5:
	printf("exiting...\n");
	break;
	
	default:
	printf("enter correct choice\n");
	break;

}

}while(choice!=5);

return 0;
}

