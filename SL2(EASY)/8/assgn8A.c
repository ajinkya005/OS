#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define TEXT_SZ 2048

struct shared_use_st 
{
	int written_by_you;
	char some_text[TEXT_SZ];
};

int main() {
	int running = 1;
	void *shared_memory = (void *)0;
	struct shared_use_st *shared_stuff;		
	char buffer[BUFSIZ];		//BUFSIZ = size of input buffer . normally 512
	int shmid;
	shmid = shmget((key_t)1, sizeof(struct shared_use_st), 0666 | IPC_CREAT);		//create shared memory . parameters key , size and flag . 0666 for only read and write not execute.

	printf("\nshared memory id : %d\n",shmid);
	if (shmid == -1) {
		fprintf(stderr, "shmget failed\n");
		exit(EXIT_FAILURE);
	}
	shared_memory = shmat(shmid, (void *)0, 0);		//attatch shared memory to the process

	if (shared_memory == (void *)-1) {
		fprintf(stderr, "shmat failed\n");
		exit(EXIT_FAILURE);
	}
	
	printf("Memory attached at %X\n", (int)shared_memory);		
	shared_stuff = (struct shared_use_st *)shared_memory;
	while(running) 
	{
		while(shared_stuff->written_by_you == 1) {
			sleep(1);
			printf("waiting for client...\n");
		}
		printf("Enter some text: ");
		fgets(buffer, BUFSIZ, stdin);
		strncpy(shared_stuff->some_text, buffer, TEXT_SZ);
		shared_stuff->written_by_you = 1;
		if (strncmp(buffer, "end", 3) == 0) 
		{
			running = 0;
		}
	}
	if (shmdt(shared_memory) == -1) {
		fprintf(stderr, "shmdt failed\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
