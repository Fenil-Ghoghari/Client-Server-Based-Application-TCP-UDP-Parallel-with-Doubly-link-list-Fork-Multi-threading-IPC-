// C Program for Message Queue for Receiver
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int receiver()
{
	key_t my_key;
	int msg_id;
	if (my_key = ftok("q_recv.h", 64) < 0) //create unique key
	{
		perror("ftok");
		exit(1);
	}
	msg_id = msgget(my_key, 0666 | IPC_CREAT);		 //create message queue and return id
	msgrcv(msg_id, &message, sizeof(message), 1, 0); //used to receive message

	printf("[+]Received Message From Queue : %s \n", message.msg);
	msgctl(msg_id, IPC_RMID, NULL); //destroy the message queue
	exit(0);
}
