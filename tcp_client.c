#include "common.h"

void err_n_die(const char *fmt, ...);

int main(int argc, char **argv)
{
    int sockfd, n;
    int sendbytes;
    struct sockaddr_in server_addr;
    char sendline[MAXLINE];
    char recvline[MAXLINE];
    
    /* Usage check */
    if(argc != 2){
        err_n_die("usage: %s <server address>", argv[0]);
    }

    /* Create a socket */
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        err_n_die("Error while creating the socket!");
    }

    /* Zero out the address */
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT); /* htons: host to network */

    /* Translate addr */
    if(inet_pton(AF_INET, argv[1], &server_addr.sin_addr) <= 0){
        err_n_die("inet_pton error for %s ", argv[1]);
    }

    /* Connect to the server */
    if(connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
        err_n_die("connect failed!");
    }

    /* Prepare the payload */
    sprintf(sendline, "GET / HTTP/1.1\r\n\r\n");
    sendbytes = strlen(sendline);

    /* Send the request */
    if(write(sockfd, sendline, sendbytes) != sendbytes){
        err_n_die("Write error!");
    }


    /* Receive the response */
    memset(recvline, 0, MAXLINE);
    while ((n = read(sockfd, recvline, MAXLINE - 1)) > 0)
    {
        printf("%s", recvline);
    }
    if(n < 0) err_n_die("Read error!");

    exit(0);
}

