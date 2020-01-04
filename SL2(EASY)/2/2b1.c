#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
void bubblesort(int arr[],int n)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(arr[j]>arr[j+1])
			{
				int temp;
				temp=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=temp;
			}
		}
	}
}
int main()
{	
    	int arr[10];
        int id,i,n;
	char *arg[20],str[15];
	printf("\n enter size of array:");
	scanf("%d",&n);
	printf("\nEnter elements of array(integers)\n");
	for(i=0;i<n;i++)
	{
		scanf("%d",&arr[i]);
	}
	printf("\nArray 1 sorting using bubble sort\n");
	bubblesort(arr,n);
	/*for(i=0;i<n;i++)
	{
		printf("%d",arr[i]);
	}*/
	id=fork();
	if(id!=0)
	{
		printf("\nparent process is running\n parent process id is %d\n parent's parent(bash) id is %d\n",getpid(),getppid());
		printf("parent process is waiting \n");
		wait();
		printf("\n back in parent\nparent is completing\n"); 
		//sleep(1);
	}
	else
	{
		printf("\nchild process is running\n child process id is %d\n child's parent process id is %d\n",getpid(),getppid());
		for(i=0;i<n;i++)
		{
			sprintf(str,"%d",arr[i]);
			arg[i]=(char *)malloc(sizeof(str));
			strcpy(arg[i],str);
		}
		arg[i]=NULL;
		printf("\ngoing in new program for searching\n");
		execve("./2b2",arg,NULL);
		printf("\n back in child\nchild is completing\n");	
	}				
}

