CFLAGS=-Wall -g

all:	gmp	client	server
	@echo "\nDone.\nYou can now run ./server on a terminal and then ./client on a different terminal."

client:
	gcc tcp_client.c -lm -lgmp -o client

server:
	gcc tcp_server.c -lm -lgmp -o server

gmp:
	sudo apt-get install libgmp3-dev
clean:
	rm -f client
	rm -f server
