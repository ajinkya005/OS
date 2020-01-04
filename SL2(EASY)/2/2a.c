#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#define sz 10
void quicksort(int arr1[],int low,int up)
{
	int ind;
	if(low<up)
	{
		ind=fix_my_ele(arr1,low,up);
		quicksort(arr1,low,ind-1);
		quicksort(arr1,ind+1,up);
	}
	
}
int fix_my_ele(int arr1[],int low ,int up)
{
	int pivot,p,q,temp;
	pivot=arr1[low];
	p=low+1;
	q=up;
	while(p<q)
	{
		while(arr1[p]<pivot&&p<=up)
			p++;
		while(arr1[q]>pivot)
			q--;
		if(p<q)
		{
			temp=arr1[p];
			arr1[p]=arr1[q];
			arr1[q]=temp;
		}
	}
	temp=arr1[q];
	arr1[q]=pivot;
	arr1[low]=temp;
	return q;
}
void mergesort(int arr1[],int low ,int up)
{
	
	if(low<up)
	{
		int mid=(low+up)/2;
		mergesort(arr1,low,mid);
		mergesort(arr1,mid+1,up);
		merge(arr1,low,mid,up);
	}
}
void merge(int arr1[],int low,int mid,int up)
{
	int temp[10];
	int i,j,k;
	i=low;
	j=mid+1;
	k=low;
	while(i<=mid&&j<=up)
	{
		if(arr1[i]<=arr1[j])
		{
			temp[k]=arr1[i];
			i++;
		}
		else
		{
			temp[k]=arr1[j];
			j++;
		}
		k++;
	}
	while(i<=mid)
	{
		temp[k]=arr1[i];
			i++;
			k++;
	}
	while(j<=up)
	{
		temp[k]=arr1[j];
			j++;
			k++;
	}
	k=low;
	for(i=low;i<=up;i++)
	{
		arr1[i]=temp[k];
		k++;
	}
}
int main()
{	
    	int arr1[10],arr2[10];
        int id,i;
	printf("\nEnter elements of array1(integers)\n");
	for(i=0;i<10;i++)
	{
		scanf("%d",&arr1[i]);
	}
	printf("\nEnter elements of array2(integers)\n");
	for(i=0;i<10;i++)
	{
		scanf("%d",&arr2[i]);
	}
	id=fork();
	if(id!=0)
	{
		printf("\nparent process is running\n parent process id is %d\n parent's parent(bash) id is %d\n",getpid(),getppid());
		printf("\nArray 1 sorting using insertion sort\n");
		//quicksort(arr1,0,9);
		insertion(arr1 , 10);
		sleep(1);
		printf("\nArray 1 after sorting :");
		for(i=0;i<10;i++)
		{
			printf("%d\n",arr1[i]);
		}
	}
	else
	{
		printf("\nchild process is running\n child process id is %d\n child's parent process id is %d\n",getpid(),getppid());
		printf("\nArray 2 sorting using bubble sort\n");
		//mergesort(arr2,0,9);
		bubble_sort(arr2 , 10);
		sleep(5);
		printf("\nArray 2 after sorting :");
		for(i=0;i<10;i++)
		{
			printf("%d\n",arr2[i]);
		}
	}
				
}



void bubble_sort(int arr[sz] , int n)
{


	int i , j , t;
	
	for(i=0 ; i<n ; i++)
	{
	
		for(j=0 ; j<n ; j++)
		{
		
			if(arr[i] < arr[j])
			{
			
				t = arr[i];
				arr[i] = arr[j];
				arr[j] = t;
					
			}
		}
	
	}
	
}


void display(int arr[sz] , int n)
{

	int i , j;
	
	for(i=0 ; i<n ; i++)
	{
		printf("\t %d",arr[i]);
	}


}

void insertion(int a[sz] , int n)
{
	
	int i , j , t , count=0;
	
	for(i=1;i<n;i++)
	{
		
		 t = a[i];
		 for(j=i ; j>0 && a[j-1]>t ; j-- )
		 	a[j] = a[j-1];
		 	
		 a[j] = t;	

	}
	
	
	
}


