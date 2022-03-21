# README FILE FOR CLIENT_SERVER APPICATION

# Basic Information Related to files:

 - This folder contain all files that's need to perform different operations mention in         assignment.

# step-1
 - Write **make** command into terminal, So we get TWO executable file server and client
# step-2
-First **server.c** file needs to be run by writing command ./server into terminal
# step-3
-For **client.c** file we need give some command line arguments.

1st argu will be **'-t'** or **'-u'** here t indicate **'TCP**' and u indicate **'UDP'**

2nd argu will be message code (i.e. 1,2 like wise), its depend on user what operation need to perform

3rd sequence number

**command**-->{ ./client (type) (operation need to perform) (seq num) }

i.e. ./client -t 1 2 --> Here Used Request to Perform Doubly Linked List Operation.

# Different Operation Server can perform namely
 1. Doubly Linked List Operation
 2. Multi-threading Operation
 3. Fork Operation
 4. IPC Mechanism

# Note
No command line arguments requires **server.c** file
