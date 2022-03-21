//Server code

#include <stdio.h> //I/O functions
#include <stdlib.h>
#include <sys/types.h>  //Different data types used in system calls
#include <sys/socket.h> //Different Structures used for sockets
#include <netinet/in.h> //Structures used for Internet Domain Address
#include <string.h>     //Different String functions
#include <unistd.h>     //provides access to POSIX s/m API

//Header file for Opeartion to pearform
#include "args.h"
#include "DLL.h"
#include "multiThread.h"
#include "FORK.h"
#include "q_sender.h"
#include "q_recv.h"
#include "pipe.h"

#define BUFFER_SIZE 255
#define PORT 8080
#define num_req 6

int main()
{
   int sockfd, newsockfd;
   int payload1[1000];
   int payload, count = 0, pos = 0, msg_code, size, cmp;
   socklen_t clilen;
   char buffer[BUFFER_SIZE];                  //buffer for storing data/msg
   struct sockaddr_in ServerAddr, ClientAddr; //structures
   int channel;

   sockfd = socket(AF_INET, SOCK_STREAM, 0); //socket creation
   if (sockfd < 0)
   {
      perror("Fail To opening socket"); //socket creation fail
      exit(1);
   }
   printf("[+]Server Socket Created Sucessfully.\n");
   bzero((char *)&ServerAddr, sizeof(ServerAddr)); //clears  data in structure
  
   //Filling the server structures data

   ServerAddr.sin_family = AF_INET;         //IPv4-domain
   ServerAddr.sin_addr.s_addr = INADDR_ANY; //IP address of local host
   ServerAddr.sin_port = htons(PORT);       //passing port no

   //bind function-used for checking whether address has been assigned or not

   if (bind(sockfd, (struct sockaddr *)&ServerAddr, sizeof(ServerAddr)) < 0)
   {
      perror(" Fail to binding");
      exit(1);
   }
   printf("[+]Binded Sucessfully.\n");
   //listen function-listens for the connection request from client

   if (listen(sockfd, num_req) < 0) // Num of req system can handel at a time.
   {
      perror("[+]Listening Fail");
      exit(1);
   }
   printf("[+]Listening Sucessfully.\n");
   clilen = sizeof(ClientAddr); //structure for client

   newsockfd = accept(sockfd, (struct sockaddr *)&ClientAddr, &clilen);
   if (newsockfd < 0)
   {
      perror("[+]Fail To Accept Connection");
      exit(1);
   }
   printf("[+]Connection Accepted.\n");
   printf("Server:");

   while (1)
   {
      bzero(buffer, BUFFER_SIZE); //clears buffer

      channel = read(newsockfd, buffer, BUFFER_SIZE); //server read from buffer
      if (channel < 0)
      {
         perror("[+]Fail To Read MSG");
         exit(1);
      }
      printf("\n");

      msg_code = buffer[4];

      if (msg_code == 1)
      {
         for (count = 9; count < 14; count++)
         {
            payload1[pos] = buffer[count];
            printf("[+]payload data is %d\n", payload1[pos]);
            pos++;
         }
      }

      else
      {
         payload = buffer[8];
      }

      size = 5;

      switch (msg_code)
      {
      case 1: //DLL operation
         dll(payload1, size);
         break;

      case 2: //Multi_threading;
         multithread();
         break;

      case 3: //FORK process
         multiple_process(payload);
         break;

      case 4:
         if (payload == 1)
         {
            sender();
            receiver();
         }

         else
         {
            msg_pipe();
         }
         break;
      }

      bzero(buffer, BUFFER_SIZE); //clears buffer

      channel = read(newsockfd, buffer, BUFFER_SIZE); //server read from buffer

      if (channel < 0)
      {
         perror("[+]Fail To Reading ");
         exit(1);
      }

      printf("Client: %s\n", buffer); //print MSG from client

      bzero(buffer, BUFFER_SIZE); //clears buffer

      fgets(buffer, BUFFER_SIZE, stdin); //Read

      channel = write(newsockfd, buffer, strlen(buffer)); //writing to the buffer
      if (channel < 0)
      {
         perror("[+]Fail To Writing ");
         exit(1);
      }
   }
   close(newsockfd); //ends the network
   close(sockfd);    //ends the socket
   return 0;
}
