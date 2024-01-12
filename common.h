#ifndef __COMMON_H__
#define __COMMON_H__

#include <sys/socket.h>
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdarg.h>
#include <errno.h>
#include <fcntl.h>
#include <arpa/inet.h>

#define SERVER_PORT     18000
#define MAXLINE         4096

void err_n_die(const char *fmt, ...);
char* bin2hex(const unsigned char *input, size_t len);


#endif // __COMMON_H__