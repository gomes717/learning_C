#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main()
{
    pid_t pid = fork();
    printf("Teste de processo\n");
    printf("parent pid: %d\n", pid);
    if(pid == 0)
    {
        printf("Inside child process\n");
    }
    else
    {
        printf("Inside Parent process\n");
        pid_t pid2 = fork();
        if(pid2 == 0)
        {
            printf("Inside child 2 process\n");
        }
        else
        {
            //printf("Inside Parent process\n");
            
        }
    }
    return 0;
}