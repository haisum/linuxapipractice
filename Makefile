CC=gcc
CFLAGS=-I.
DEPS=mysocket.o
TARGETS=unix_client unix_server

all: $(TARGETS)

unix_client:	unix_server	unix_client.o	$(DEPS) 
	$(CC) -o unix_client unix_client.o $(DEPS) $(CFLAGS)

unix_server:	unix_server.o	$(DEPS) 
	$(CC) -o unix_server unix_server.o $(DEPS) $(CFLAGS)

%.o:	%.c
	$(CC) -c *.c $(CFLAGS)

clean:
	rm unix_client unix_server *.o