#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
int A[10][10],B[10][10];
long int C[10][10];
int t=1;
void* mul_thread(void * arg)
{
	int row,col,k,*rcargs,z,i;
	long int ret_value=0;
	rcargs=(int *)arg;
	row=rcargs[0];
	col=rcargs[1];
	k=rcargs[2];
	printf("\n\tThread No %d-%d joined",row+1,col+1);
	for(i=0;i<k;i++)
	{
		ret_value = ret_value + A[row][i] * B[i][col];
		printf("\n%d - Thread No %d-%d - Calculated %d x %d = %d --> %ld",t,row+1,col+1,A[row][i],B[i][col],A[row][i]*B[i][col],ret_value);
		z=rand()%10;
		printf("\n%d - Thread No %d-%d Paused -- Sleeping for %d units",t, row+1,col+1,z);
		sleep(z);
		printf("\n%d - Thread No %d-%d .......Resumed",t, row+1,col+1);
		t++;
	}
	printf("\n...........Thread No %d-%d ............................exits", row+1,col+1);
	pthread_exit((void *) ret_value);	
}
void accept_matrix(int M[10][10], int rows, int cols) {
	int i, j;
	printf("\n");
	for(i=0;i<rows;i++)
	{
		for(j=0;j<cols;j++) 
		{
			printf("Value at [%d][%d]: ",i+1,j+1);
			scanf("%d",&M[i][j]);
		}
	}
}
void display_matrix(int M[10][10], int rows, int cols) 
{
	int i, j;
	printf("\n");	
	for(i=0;i<rows;i++)
	{
		for(j=0;j<cols;j++)
		{
			printf("%d  ",M[i][j]);
		}
		printf("\n");
	}
}
int main()
{
	int rows_A, cols_A, rows_B, cols_B;
	int rcArgs[3];
	int i, j, k, *status;
	pthread_t P[10][10];
	
	printf("\nEnter no. of rows in matrix A: ");
	scanf("%d",&rows_A);
	printf("Enter no. of columns in matrix A: ");
	scanf("%d",&cols_A);


        printf("\nEnter no. of rows in matrix B: ");
	scanf("%d",&rows_B);
	printf("Enter no. of columns in matrix B: ");
	scanf("%d",&cols_B);

        
	if(cols_A != rows_B) 
	{
		
		printf("\n Matrix multiplication not possible.");
                printf("\nEnter no. of rows in matrix A: ");
		scanf("%d",&rows_A);
		printf("Enter no. of columns in matrix A: ");
		scanf("%d",&cols_A);


        	printf("\nEnter no. of rows in matrix B: ");
		scanf("%d",&rows_B);
		printf("Enter no. of columns in matrix B: ");
		scanf("%d",&cols_B);
	}
       

	accept_matrix(A, rows_A, cols_A);
	accept_matrix(B, rows_B, cols_B);
	
	for(i=0;i<rows_A;i++)
	{
		for(j=0;j<cols_B;j++)
		{
			rcArgs[0]=i;
			rcArgs[1]=j;
			rcArgs[2]=cols_A;
			if(pthread_create(&P[i][j],NULL,mul_thread,rcArgs)!=0)
				printf(" Cannot create thread.\n");
			else
			{
				printf(" Thread no %d-%d created\n",i+1,j+1);
				sleep(2);
            		}
		}
	}

	printf("\n\nMatrix A : \n");
	display_matrix(A, rows_A, cols_A);
	printf("\nMatrix B : \n");
	display_matrix(B, rows_B, cols_B);
	
	for(i=0;i<rows_A;i++) 
	{
		for(j=0;j<cols_B;j++) 
		{
            {
				if(pthread_join(P[i][j],(void **) &status) != 0)
					perror("\nThread join failed.\n");
				C[i][j] = (long int)status;
			}
		}
	}
	
	printf("\n\nMatrix C : \n");
	for(i=0;i<rows_A;i++){
		for(j=0;j<cols_B;j++){
			printf("%ld  ",C[i][j]);
		}
		printf("\n");
	}
	printf("\n------------------------------------------------------\n\n");
	exit(EXIT_SUCCESS);
}


	
	
 
