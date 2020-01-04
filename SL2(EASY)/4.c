#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#define buffer_size 5

typedef struct 
{
	int in,out;
	sem_t full, empty;
	int arr[buffer_size];
    pthread_mutex_t lock;
}buffer;
buffer b;
int item=1;
void *producer(void * num)
{
	int i,z,value;
	i=*(int *)num;		//The (int *) part casts the variable number to a pointer to an int, then the * in front dereferences it to an int.
	printf("producer %d preparing to produce\n",i);
	while(1) 	
	{
		z=(rand()%10)+1;
		sleep(z);
		sem_wait(&b.empty);		//sem_wait() decrements (locks) the semaphore pointed to by sem.
		sem_getvalue(&b.empty,&value);	// sem_getvalue() places the current value of the semaphore pointed to sem into the integer pointed to by sval.
       
		if(value==0)
			printf("Buffer full. producer %d waiting for consumer to consume\n",i);
		else
		{
			pthread_mutex_lock(&b.lock);
			printf("producer %d produced %d item\n",i,item);
			b.arr[(b.in++)%buffer_size]=item++;
			pthread_mutex_unlock(&b.lock);
			sem_post(&b.full);	//sem_post() increments (unlocks) the semaphore pointed to by sem.
		}
	} 
}
void *consumer(void * num)
{
	int i,z,value,cons;
	i=*(int *)num;
	printf("\t\t\tconsumer %d preparing to consume\n",i);
	while(1)
	{
		z=(rand()%10)+1;
		sleep(z);
		sem_wait(&b.full);
		sem_getvalue(&b.full,&value);
		if(value==buffer_size)
			printf("\t\t\tBuffer empty. consumer %d waiting for producer to produce\n",i);
		else
		{
			pthread_mutex_lock(&b.lock);
			cons=b.arr[(b.out++)%buffer_size];
			printf("\t\t\tconsumer %d consumed %d item\n",i,cons);
			pthread_mutex_unlock(&b.lock);
			sem_post(&b.empty);
		}
	} 
}
void init()
{
	b.in=0;
	b.out=0;
	sem_init(&b.empty,0,buffer_size);
	sem_init(&b.full,0,0);
	pthread_mutex_init(&b.lock,NULL);
}
int main()
{
	int np,nc;
	int c[]={1,2,3,4,5,6,7,8,9,10};
	pthread_t p_id[buffer_size],c_id[buffer_size];
	printf("Enter no of producers::");
	scanf("%d",&np);
	printf("Enter no of consumers::");
	scanf("%d",&nc);
	init();
	for(int i=0;i<np;i++)
	{
		pthread_create(&p_id[i],NULL,producer,&c[i]);
		printf("----------------------------Thread created for %d producer-----------------------\n",i+1);
	}
	for(int i=0;i<nc;i++)
	{
		pthread_create(&c_id[i],NULL,consumer,&c[i]);
		printf("----------------------------Thread created for %d consumer-----------------------\n",i+1);
	}
	for(int i=0;i<np;i++)
	{
		pthread_join(p_id[i],NULL);
		printf("-----------------------Thread joined for %d producer\n-----------------------",i+1);
	}
	for(int i=0;i<nc;i++)
	{
		pthread_join(c_id[i],NULL);
		printf("-----------------------Thread joined for %d consumer\n-----------------------",i+1);
	}
}
