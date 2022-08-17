#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#define ARR_SIZE 6

pthread_barrier_t barrier;

void *routine(void* args)
{
    for(int i = 0; i < 5; i++)
    {
        printf("waiting in barrier\n");
        pthread_barrier_wait(&barrier);
        printf("Passed\n");
        sleep(1);
    }
	free(args);
}



int main()
{
	pthread_t th[ARR_SIZE];
    pthread_barrier_init(&barrier, NULL, ARR_SIZE/3);
	for(int i = 0; i < ARR_SIZE; i++)
	{
		int* arg = (int*) malloc(sizeof(int));
		*arg = i;
        if(pthread_create(&th[i], NULL, routine, arg))
        {
            printf("thread 1 not created\n");
            exit(0);
        }
        
    }
	
	for(int i = 0; i < ARR_SIZE; i++)
	{
		pthread_join(th[i], NULL);
	}

	return 0;
}
