// c program that perform Fork operation
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <signal.h>

void multiple_process(int number)
{
	int count, select, i;
	pid_t pid; 

	printf("\n*********** Select Any Operation *************\n");
	printf("[-]1.Create child processes\n[-]2.kill child processes\n[-]3.child processes with IDs\n[-]4.Exit\nEnter your select: ");

	while (1)
	{

		scanf("%d", &select);

		switch (select)
		{
		case 1:
			for (count = 0; count < number; count++)
			{
				if ((pid = fork()) == 0)
				{
					printf("[+]Child process %d\n", i + 1);
				}
			}
			break;

		case 2:
			kill(pid, SIGINT);
			break;

		case 3:
			for (i = 0; i < number; i++)
			{
				if ((pid = fork()) == 0)
				{
					printf("[+][Clild] pid %d from [parent] pid %d\n", getpid(), getppid());
				}
			}
			break;

		case 4:
			exit(0);
			break;
		}
	}
}
