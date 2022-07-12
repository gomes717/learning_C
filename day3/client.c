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
    int sock_fd;
    int n;
    int send_bytes;
    struct sockaddr_in serv_addr;
    char send_line[MAXLINE];
    char recv_line[MAXLINE];

    if(argc != 2)
    {
        printf("Missing argument: %s <server_address>\n", argv[0]);
        exit(0);
    }

    if((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Error: failed to create socket\n");
        exit(0);
    }

    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERVER_PORT);

    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0)
    {
        printf("inet_pton error for %s\n", argv[1]);
        exit(0);
    }

    if(connect(sock_fd, (SA*) &serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("Connection failed\n");
        exit(0);
    }

    send_bytes = sprintf(send_line, "GET / HTTP/1.1\r\n\r\n");
    printf("Sending...\n");
    if(write(sock_fd, send_line, send_bytes) != send_bytes)
    {
        printf("Write error\n");
        exit(0);
    }

    printf("Receiving...\n");
    memset(recv_line, 0, MAXLINE);
    while((n = read(sock_fd, recv_line, MAXLINE-1)) > 0)
    {
        printf("%s", recv_line);
        memset(recv_line, 0, MAXLINE);
    }

    if(n < 0)
    {
        printf("Read error\n");
        exit(0);
    }

    return 0;

}