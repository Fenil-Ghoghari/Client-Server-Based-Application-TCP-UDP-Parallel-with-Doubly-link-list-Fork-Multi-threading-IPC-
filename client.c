//Client program

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "args.h"

#define buffer_size 255
#define PORT 8080

int main(int argc, char *argv[])
{
    int sockfd, channel, count, counter, fun_3, fun_5;
    struct sockaddr_in serv_addr;
    struct hostent *server; //Provide info related to host-host name, ip address
    const char *name = "127.0.0.1";
    char *fun_1;
    char *fun_2;
    char *fun_4;
    char buffer[buffer_size];     //buffer for storing data
    server = gethostbyname(name); //storing server's IP address

    sockfd = socket(AF_INET, SOCK_STREAM, 0); //creating socket for communication
    if (sockfd < 0)
    {
        perror("Fail to opening socket");
        exit(1);
    }
    printf("[+]Client Socket Created Sucessfully.\n");

    bzero((char *)&serv_addr, sizeof(serv_addr));

    //server structure

    serv_addr.sin_family = AF_INET; //IPv4 Domain address
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);

    serv_addr.sin_port = htons(PORT); //port no

    //connect function

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Fail TO connecting");
        exit(1);
    }
    printf("[+]Connected Sucessfully.\n");

    //Sending MSG Fram
    printf("Client: ");

    while (1)
    {
        struct MSG_fram_str *ptr = inputs(argc, argv); //calls arguments from args.h

        bzero(buffer, buffer_size); //clears the buffer

        char *fun_1 = ptr->seq_num; //passing seq_num
        strcpy(buffer, fun_1);      //copy sequence no to buffer

        char *fun_2 = ptr->type; //passing type udp/tcp
        strcat(buffer, fun_2);

        fun_3 = ptr->msg_code; //passing msg_code
        buffer[4] = fun_3;

        char *fun_4 = ptr->output_type; //passing output_type
        strcat(buffer, fun_4);

        if (fun_3 == 1)
        {
            counter = 8;
            for (count = 0; count < 5; count++)
            {
                buffer[counter] = ptr->payload1[count];
                counter++;
            }
        }

        else
        {
            fun_5 = ptr->payload;
            buffer[8] = fun_5;
        }

        channel = write(sockfd, buffer, strlen(buffer)); //client write MSG into the buffer

        bzero(buffer, buffer_size);                      //clears the buffer
        fgets(buffer, buffer_size, stdin);               // Reading the MSG to be sent
        channel = write(sockfd, buffer, strlen(buffer)); //client write MSG into the buffer

        if (channel < 0)
        {
            perror("Fail To Sending MSG");
            exit(1);
        }

        bzero(buffer, buffer_size);                  //clears buffer
        channel = read(sockfd, buffer, buffer_size); //reads from the buffer

        if (channel < 0)
        {
            perror("Fail To received MSG from socket");
            exit(1);
        }

        printf("\n");
        printf("Server : %s\n", buffer);
    }
    close(sockfd); //closes the socket
    return 0;
}
