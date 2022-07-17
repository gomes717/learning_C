#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>


int main()
{
    pid_t pid = fork();
    int n;
    if(pid == 0)
    {
        n = 1;
    }
    else
    {
        n = 6;
        wait();
    }


    for(int i = n; i < n+5; i++)
    {
        printf("%d ", i);
        fflush(stdout);
    }
    return 0;
}