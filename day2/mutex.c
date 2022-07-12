#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

int g_var = 0;
pthread_mutex_t var_count;

void *threadFunc()
{
	for(size_t i = 0; i < 100000; i++)
	{
        pthread_mutex_lock(&var_count);
		g_var++;
        pthread_mutex_unlock(&var_count);
	}
}

int main()
{
	pthread_t t1, t2;

    pthread_mutex_init(&var_count, NULL);

	if(pthread_create(&t1, NULL, threadFunc, NULL))
	{
		printf("thread 1 not created\n");
		exit(0);
	}

    if(pthread_create(&t2, NULL, threadFunc, NULL))
	{
		printf("thread 2 not created\n");
		exit(0);
	}

	printf("threads created\n");

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);


    printf("g_var: %d\n", g_var);

	return 0;
}
