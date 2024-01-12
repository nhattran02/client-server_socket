CC = gcc
CFLAGS = -I.
COMMON_SRC = common.c 

all: tcp_client tcp_server

tcp_client: tcp_client.c $(COMMON_SRC)
	$(CC) tcp_client.c $(COMMON_SRC) -o tcp_client  $(CFLAGS)

tcp_server: tcp_server.c $(COMMON_SRC)
	$(CC) tcp_server.c $(COMMON_SRC) -o tcp_server  $(CFLAGS)

clean: 
	rm -rf tcp_client tcp_server