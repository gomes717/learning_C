#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>


int main()
{
    pid_t pid = fork();

    if(pid == 0)
    {
        sleep(1);
    }

    printf("Current ID: %d\n", getpid());
    printf("Parent ID: %d\n", getppid());

    int res = wait(NULL);
    if(res == -1)
    {
        printf("Process without child\n");
    }
    else
    {
        printf("child with id %d has finished\n", res);
    }
    return 0;
}