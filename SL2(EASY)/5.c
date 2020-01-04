#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
	

sem_t wrt;		//declaring semaphore
pthread_mutex_t m;		//declaration of mutex
int read_count=0;
int buffer;

//only one writer may right at a time
//If a writer is writing to the file, no reader may read it.
//Any number of readers may simultaneously read the file

void * writer(void *args){		//will pass number of arguments

	while(1){		
		sleep(rand()%7);
		sem_wait(&wrt);
		//critical section
				printf("\nIN WRITER...");
				buffer = rand()%222;
				printf("\nWRITER GENERATED VALUE : %d\n",buffer);
				sleep(1);
		sem_post(&wrt);
	}	
	pthread_exit(NULL);
}

void * reader(void *args){		//will pass number of arguments
	int i;
	int pos = *(int *)args;
	while(1){
		sleep(rand()%7);
		pthread_mutex_lock(&m);
		//critical section
				read_count++;
				if(read_count == 1){
					sem_post(&wrt);
				}
				pthread_mutex_unlock(&m);
				
				printf("\nIN READER...%d\n",pos);
				printf("\nBUFFER IS : \n{ %d }\n",buffer);
					sleep(1);
				pthread_mutex_lock(&m);
				read_count--;
				if(read_count == 0){
					sem_wait(&wrt);
				}
				pthread_mutex_unlock(&m);
	}
	pthread_exit(NULL);
}

int main(){
	int *b,err,p,c,i;
	pthread_t *thread1,*thread2;		//declaration of thread
	int pshared;						//wheather semaphore is shared between the threads i.e = 0
										//or shared between the processes i.e != 0

	printf("HOW MANY READERS ?\n");
	scanf("%d",&c);

	err = pthread_mutex_init(&m,NULL);			//mutex initialization
	if(err!=0){
		printf("MUTEX INITIALIZATION FAILED\n");
		exit(EXIT_FAILURE);
	}
	err = sem_init(&wrt,0,0);				//semaphore initialization
	if(err !=0){
		printf("SEMAPHORE INITIALIZATION FAILED...\n");
		exit(EXIT_FAILURE);
	}

	thread1 = (pthread_t *) malloc(sizeof(pthread_t));		//allocating p threads
	thread2 = (pthread_t *) malloc(c*sizeof(pthread_t));		//allocating c threads
	
	printf("\n:::::::::::::::::::::CREATING THREADS:::::::::::::::::::\n");

			err = pthread_create(thread1,NULL,writer,NULL);
			if(err!=0){
				printf("THREAD CREATION FAILED...\n");
				exit(EXIT_FAILURE);
			}
	
	
	for(i=0;i<c;i++){			//consumer thread creation
			b = &i;	//to know which consumer is consuming
			err = pthread_create((thread2+i),NULL,reader,b);
			if(err!=0){
				printf("THREAD CREATION FAILED...\n");
				exit(EXIT_FAILURE);
			}
	}

	printf("\n:::::::::::::::::JOINING THREADS ::::::::::::\n");

		err = pthread_join(*(thread1), NULL);	
			// check for thread join failure
			if (err != 0) {
				printf("Thread join failed");
				exit(EXIT_FAILURE);
			}


	for(i=0;i<c;i++){
		err = pthread_join(*(thread2+i), NULL);	
			// check for thread join failure
			if (err != 0) {
				printf("Thread join failed");
				exit(EXIT_FAILURE);
			}
	}
	sem_destroy(&wrt);

	printf("PROGRAM FINISHED...\n");
	
}
