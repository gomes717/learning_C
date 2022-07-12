#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>
#define ARR_SIZE 5

int fuel = 0;
pthread_mutex_t fuel_mutex;
pthread_cond_t fuel_cond;

void *fillingFuel(void* args)
{
    for(int i = 0; i < 5; i++)
    {
        pthread_mutex_lock(&fuel_mutex);
        fuel += 60;
        printf("Filling fuel ... %d\n", fuel);
        pthread_mutex_unlock(&fuel_mutex);
        //pthread_cond_signal(&fuel_cond);
        pthread_cond_broadcast(&fuel_cond);
        sleep(1);
    }
	free(args);
}

void *car(void* args)
{
    pthread_mutex_lock(&fuel_mutex);
    while(fuel < 40 )
    {
        printf("Waiting for fuel... car:%d\n", *(int*)args);
        pthread_cond_wait(&fuel_cond, &fuel_mutex);
    }
    fuel -= 40;
    printf("Got fuel. Now left: %d \t car: %d\n", fuel, *(int*)args);
    pthread_mutex_unlock(&fuel_mutex);
	free(args);
}

int main()
{
	pthread_t th[ARR_SIZE];
	pthread_mutex_init(&fuel_mutex, NULL);
    pthread_cond_init(&fuel_cond, NULL);

	for(int i = 0; i < ARR_SIZE; i++)
	{
		int* arg = (int*) malloc(sizeof(int));
		*arg = i;
        if(i == ARR_SIZE - 1)
        {
            if(pthread_create(&th[i], NULL, fillingFuel, arg))
            {
                printf("thread 1 not created\n");
                exit(0);
            }
        }
        else
        {
            if(pthread_create(&th[i], NULL, car, arg))
            {
                printf("thread 1 not created\n");
                exit(0);
            }
        }
	}
	
	for(int i = 0; i < ARR_SIZE; i++)
	{
		pthread_join(th[i], NULL);
	}

	pthread_mutex_destroy(&fuel_mutex);
	pthread_cond_destroy(&fuel_cond);

	return 0;
}
