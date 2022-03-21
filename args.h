enum do_operation
{
	Doubly_Link_List = 1,
	Multi_Threading = 2,
	Fork = 3,
	IPC = 4
};
struct MSG_fram_str
{
	char *seq_num;
	char *type;					//tcp or udp
	enum do_operation msg_code; //operation that neeeds to be performed
	char *output_type;			//tcp or udp
	int payload;				//payload
	int payload1[100];
	int payload_size; //size of payload
};

struct MSG_fram_str *inputs(int argc, char *argv[])
{
	int choice = 0;
	int count, select;
	int Link_list[5];
	struct MSG_fram_str *msg_ptr;

	msg_ptr = (struct MSG_fram_str *)malloc(sizeof(struct MSG_fram_str));
	while (1)
	{
		while ((choice = getopt(argc, argv, "t:u:")) != -1)
		{
			switch (choice)
			{
			case 't':
				printf("[+]Perform TCP Operation\n");
				(msg_ptr)->seq_num = argv[3];
				(msg_ptr)->type = "tcp_prot";
				(msg_ptr)->msg_code = atoi(optarg);
				(msg_ptr)->output_type = "tcp_prot";
				break;

			case 'u':
				printf("[+]Perform UDP operation\n");
				(msg_ptr)->seq_num = argv[3];
				(msg_ptr)->type = "udp_prot";
				(msg_ptr)->msg_code = atoi(optarg);
				(msg_ptr)->output_type = "udp_prot";
				break;

			default:
				printf("Incorrect choice\n");
			}
		}

		switch (msg_ptr->msg_code)
		{
		case 1:
			printf("[+]ENTER DATA:");

			for (count = 0; count < 5; count++)
			{
				scanf("%d", &Link_list[count]);
				msg_ptr->payload1[count] = Link_list[count];
			}
			break;

		case 2:
			printf("[+]Multithreading operation\n");
			break;

		case 3:
			printf("[+]FORK operation\n");
			printf("[+]Enter The num of processes to be Created:\n");
			scanf("%d", &(msg_ptr->payload));
			break;

		case 4:
			printf("[+]IPC Mechanism operation\n");
			printf("[+]Select Any one IPC operation\n[-]1.MSG Queue\n[-]2.PIPE\n");
			scanf("%d", &select);
			msg_ptr->payload = select;
			break;
		}

		(msg_ptr)->payload_size = sizeof((msg_ptr)->payload);
		return msg_ptr;
	}
}
