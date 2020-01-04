#include<stdio.h>
int binary_search(int arr[],int low,int high,int key)
{
	int mid=(low+high)/2;
	if(key==arr[mid])
	{
		return mid;
	}
	else if(key>arr[mid] && low<high)
	{
		return binary_search(arr,mid+1,high,key);
	}
	else if(key<arr[mid] && low<high)
		return binary_search(arr,low,mid-1,key);
	else
		return -1;
}
int main(int argc,char* argv[])
{
	int key,i,arr[20],ind;
	printf("\nargc:%d",argc);
	printf("\nArray is:\n");
	for(i=0;i<argc;i++)
	{
		arr[i]=atoi(argv[i]);
		printf("%d\t",arr[i]);
	}
	printf("\nEnter key to search:");
	scanf("%d",&key);
	ind=binary_search(arr,0,argc-1,key);
	if(ind!=-1)
	printf("\nkey found at %d location",ind+1);
	else
	printf("\nkey not found\n");
}
	
