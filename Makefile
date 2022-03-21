cc=gcc      
MAKE=make
RM =rm

all: client.c server.c
	$(cc) client.c -o client
	$(cc) server.c -o server -lpthread
	$(MAKE) main_server

dll_t:
	./client -t 1 2

dll_u:
	./client -u 1 2

multithread_t:
	./client -t 2 2

multithread_u:
	./client -u 2 2

fork_t:
	./client -t 3 2

fork_u:
	./client -u 3 2

ipc_t:
	./client -t 4 2

ipc_u:
	./client -u 4 2

main_server:
	./server

clean: client server
	$(RM) client
	$(RM) server



