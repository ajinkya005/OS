// C program to implement one side of FIFO 
// This side reads first, then reads 
#include <stdio.h> 
#include<stdlib.h>
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 

int main() 
{ 
	int fd1; 
	int i=0,chars=0,word=1,line=1;
	// FIFO file path 
	char * myfifo = "/home/nllab13/33130/myfifo"; 

	// Creating the named file(FIFO) 
	// mkfifo(<pathname>,<permission>) 
	mkfifo(myfifo, 0666); 

	char str1[80], str2[80]; 
	while (1) 
	{
		printf("\n Waiting for file 1 to write \n");
		wait(NULL);
		// First open in read only and read 
		fd1 = open(myfifo,O_RDONLY); 
		read(fd1, str1, 80);
		// Print the read string and close 
		printf("\n User1: %s\n", str1);  
		i=0;
		chars=0;
		word=1;
		line=1;
		while(str1[i]!='\0')
		{
			if(isalnum(str1[i]))
			{
				chars++;
			}
			if(str1[i]==' ')
			{
				word++;
			}
			if(str1[i]=='.'&&str1[i+1]==' ')
			{
				line++;
			}
			i++;		
		}
		sprintf(str2, "No of characters= %d \nNo of words= %d \nNo of lines= %d\n", chars, word, line);
		close(fd1); 
		// Now open in write mode and write 
		// string taken from user. 
		printf("\n file 2 to write \n");
		fd1 = open(myfifo,O_WRONLY); 
		write(fd1, str2, strlen(str2)+1); 
		close(fd1); 
	} 
	return 0; 
} 


