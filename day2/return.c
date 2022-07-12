#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

void *threadDice()
{
	int dado = (rand()%6) +1;
    int* result = (int*) malloc(sizeof(int));
    *result = dado;
    printf("Address of returned in thread: %p\n", result);
    return (void*) result;
}

int main()
{
	pthread_t t1;
	int* returned;

	if(pthread_create(&t1, NULL, threadDice, NULL))
	{
		printf("thread 1 not created\n");
		exit(0);
	}

	pthread_join(t1, (void**) &returned);

	printf("Address of returned in main: %p\n", returned);
	printf("result of threadDice: %d\n", *returned);
	free(returned);

	return 0;
}
