CFLAGS=-Wall -g

all:	gmp	client	server
	@echo "\nDone.\nYou can now run ./server on a terminal and then ./client on a different terminal."

client:	tcp_client.c	tcp_server.c
	gcc tcp_client.c -lm -lgmp -o client

server:	tcp_server.c	tcp_client.c
	gcc tcp_server.c -lm -lgmp -o server

gmp:
	sudo apt-get install libgmp3-dev
clean:
	rm -f client
	rm -f server
