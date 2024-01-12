#include "common.h"

int main(int argc, char **argv)
{
    int listen_fd, conn_fd, n;
    struct sockaddr_in server_addr;
    uint8_t buf[MAXLINE + 1];
    uint8_t recv_buf[MAXLINE + 1];
    
    /* Create a listen socket */
    if((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        err_n_die("socket error.");
    }

    /* Zero out the address */
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(SERVER_PORT);

    /* Listen & Bind */
    if(bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0 ){
        err_n_die("bind error");
    }
    if(listen(listen_fd, 10) < 0){
        err_n_die("listen error");
    }

    while (1)
    {
        struct sockaddr_in addr;
        socklen_t addr_len;
        printf("Waiting for a connection on port %d\n", SERVER_PORT);
        fflush(stdout);
        /* Wait until an incoming connection arrives */
        conn_fd = accept(listen_fd, (struct sockaddr*)NULL, NULL);    

        /* Zero out the receive buffer */
        memset(recv_buf, 0, MAXLINE);

        /* Read client's message */
        while((n = read(conn_fd, recv_buf, MAXLINE - 1)) > 0)
        {
            fprintf(stdout, "\n%s\n\n%s", bin2hex(recv_buf, n), recv_buf);

            /* Detect the end of message */
            if(recv_buf[n - 1] == '\n'){
                break;
            }
            memset(recv_buf, 0, MAXLINE);
        }
        if(n < 0){
            err_n_die("read error");
        }

        /* Server send a response to client */
        snprintf((char *)buf, sizeof(buf), "HTTP/1.0 200 OK\r\n\r\nHello");
        write(conn_fd, (char*)buf, strlen((char*)buf));
        close(conn_fd);
    }
}

