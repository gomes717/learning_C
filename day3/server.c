#include <sys/socket.h>
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdarg.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <netdb.h>

#define SERVER_PORT 18000

#define MAXLINE 4096
#define SA struct sockaddr

int main(int argc, char** argv)
{
    int listen_fd;
    int conn_fd;
    int n;
    struct sockaddr_in serv_addr;
    char buff[MAXLINE];
    char recv[MAXLINE];

    if((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Error: socket create");
        exit(0);
    }

    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(SERVER_PORT);

    if(bind(listen_fd, (SA*) &serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("Error: Bind error");
        exit(0);
    }

    if(listen(listen_fd, 10) < 0)
    {
        printf("Error: Listen error");
        exit(0);
    }

    while(1)
    {
        struct sockaddr_in addr;
        socklen_t addr_len;

        printf("Waiting for a connection on port %d\n", SERVER_PORT);
        fflush(stdout);
        conn_fd = accept(listen_fd, (SA*) NULL, NULL);

        memset(recv, 0, MAXLINE);
        while((n = read(conn_fd, recv, MAXLINE-1)) > 0)
        {
            printf("%s\n", recv);

            if(recv[n-1] == '\n')
            {
                break;
            }

            memset(recv, 0, MAXLINE);
        }

        if(n < 0)
        {
            printf("Error: read error");
            exit(0);
        }

        n = snprintf((char*)buff, sizeof(buff), "HTTP/1.0 200 OK\r\n\r\nMensagem de retorno");

        if(n < 0)
        {
            printf("Error: snprintf error");
            exit(0);
        }

        write(conn_fd, (char*)buff, n + 1);
        close(conn_fd);
    }

}