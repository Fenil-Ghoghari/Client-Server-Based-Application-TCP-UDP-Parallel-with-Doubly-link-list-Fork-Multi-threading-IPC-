// c Program that perform multithreading operation

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

pthread_t tid[2]; //thread's structure for creating thread variables
int counter;
pthread_mutex_t lock; //variable to create mutex

void *perform_fun()
{
	pthread_mutex_lock(&lock); //function to lock the mutex

	unsigned long count = 0;
	counter += 1;
	printf("\n Opration %d has started\n", counter);

	for (count = 0; count < (0xFFFFFF); count++)
	;

	printf("\n Operation %d has finished\n", counter);

	pthread_mutex_unlock(&lock); //function to free the mutex

	return NULL;
}

int multithread(void)
{
	int i = 0;
	int error;
	int select;
	while (1)
	{
		printf("\n*********** Select Any Oparation *************\n");
		printf("1. [-]Create Thread & Display\n2. [-]Delete Thread\n3. [-]Exit\nEnter your select: ");
		scanf("%d", &select);

		switch (select)
		{
		case 1:
			if (pthread_mutex_init(&lock, NULL) != 0)
			{
				printf("\n [+]Fail to Initilized\n");
				return 1;
			}

			while (i < 2)
			{
				error = pthread_create(&(tid[i]), NULL, &perform_fun, NULL);
				if (error != 0)
					printf("\n[+]Thread creation Fail :[%s]",
						   strerror(error));
				i++;
			}

			pthread_join(tid[0], NULL); //wait for process
			pthread_join(tid[1], NULL);
			break;

		case 2:

			pthread_exit(NULL);
			pthread_mutex_destroy(&lock); //Destroying the Thread
			break;

		case 3:
		default:
			exit(0);
		}
	}

	return 0;
}
