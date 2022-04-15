#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

void *threadFunc()
{
	for(size_t i = 0; i < 5; i++)
	{
		printf("inside threadFunc(): %d\n", i);
		sleep(2);
	}
	return NULL;
}

void *threadFuncInput(void *input)
{
	printf("inside thread printing: %s\n", (char*) input);
	pthread_exit(NULL);
}

int main()
{
	pthread_t thread;

	if(pthread_create(&thread, NULL, threadFunc, NULL))
	{
		printf("thread not created\n");
		exit(0);
	}
	
	printf("thread created\n");
	for(size_t i = 0; i < 10; i++)
	{
		printf("inside main() %d\n", i);
		sleep(1);
	}

	char name[50];
	printf("write your name: \n");
	fgets(name, 50, stdin);
	pthread_t input_thread;
	if(pthread_create(&input_thread, NULL, threadFuncInput, name))
        {
                printf("thread input not created\n");
                exit(0);
        }
	pthread_join(input_thread, NULL);


	return 0;
}
