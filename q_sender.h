// C Program for Message Queue for sender
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>

struct msg_buffer
{
	long msg_type;
	char msg[100];
} message;

int sender()
{
	 key_t my_key;
    int msg_id;
    if (my_key = ftok("q_sender.h", 64) == -1) //create unique key
    {
        perror("ftok");
        exit(1);
    }
    msg_id = msgget(my_key, 0666 | IPC_CREAT); //create message queue and return id
    printf("[+]Write Message To Queue: ");
    fgets(message.msg, 100, stdin);
    msgsnd(msg_id, &message, sizeof(message), 0); //send message
    printf("[+]Sent Message Queue : %s \n", message.msg);
}
