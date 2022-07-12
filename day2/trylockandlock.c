#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>
#define ARR_SIZE 4

int g_var = 0;
pthread_mutex_t var_mutex;

void *routineLock(void* args)
{
    pthread_mutex_lock(&var_mutex);
    printf("Lock func %d\n", *(int*)args);
	sleep(1);
    pthread_mutex_unlock(&var_mutex);
	free(args);
}

void *routineTryLock(void* args)
{
    int status = pthread_mutex_trylock(&var_mutex);
	if(status == 0)
	{
    	printf("Trylock func %d\n", *(int*)args);
		sleep(1);
    	pthread_mutex_unlock(&var_mutex);
	}
	else
	{
		printf("Not locked in trylock func %d \t status: %d\n", *(int*)args, status);
	}
	free(args);
}

int main()
{
	pthread_t th[ARR_SIZE];
	pthread_mutex_init(&var_mutex, NULL);

	for(int i = 0; i < ARR_SIZE; i++)
	{
		int* arg = (int*) malloc(sizeof(int));
		*arg = i;
		if(pthread_create(&th[i], NULL, routineLock, arg))
		{
			printf("thread 1 not created\n");
			exit(0);
		}
	}
	
	for(int i = 0; i < ARR_SIZE; i++)
	{
		pthread_join(th[i], NULL);
	}

	// Using trylock 
	for(int i = 0; i < ARR_SIZE; i++)
	{
		int* arg = (int*) malloc(sizeof(int));
		*arg = i;
		if(pthread_create(&th[i], NULL, routineTryLock, arg))
		{
			printf("thread 1 not created\n");
			exit(0);
		}
	}
	
	for(int i = 0; i < ARR_SIZE; i++)
	{
		pthread_join(th[i], NULL);
	}

	pthread_mutex_destroy(&var_mutex);
	

	return 0;
}
