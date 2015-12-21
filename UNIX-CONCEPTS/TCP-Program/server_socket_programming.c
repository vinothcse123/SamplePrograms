
#include"stdio.h"
#include<sys/socket.h> // socket(),bind(),listen(),accept()
#include <arpa/inet.h> //inet_hton
#include<errno.h>  //Perror
#include<stdlib.h>
#include<string.h>
#include<unistd.h>  // close()

int main()
{
   int socketFD=-1;  // here assigned to -1 because the function will return 0 if success
   int bind_status=-1;
   char buffer[100];

   printf("\nGoing to allocate resource for socket! We have passed family type,connection type,protocol name");

   socketFD=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);

   if(socketFD!=-1)
   {
      printf("\nSuccessfully allocated resources and created FD with id %d",socketFD);
   }
   else
   {
      perror("\nError in socket() ");
      exit(EXIT_FAILURE);
   }

   printf("\n\nGoing to allocate the IPaddress and port number to the socket resources allocated.");

   struct sockaddr_in stSockaddr;
   memset(&stSockaddr,'\0',sizeof(stSockaddr));
   stSockaddr.sin_family=AF_INET;
   stSockaddr.sin_port=htons(1200);
   stSockaddr.sin_addr.s_addr=inet_addr("192.168.151.71");


   //Not to invoke  there

   bind_status=bind(socketFD,(struct sockaddr *) &stSockaddr,sizeof(stSockaddr));

   if(bind_status==-1)
   {
      perror("Error in binding the socket with given socket fd and ipaddress ERR DESC:\n");
      close(socketFD);
      exit(EXIT_FAILURE);
   }
   else
   {
      printf("\nSuccessfully binded the  IPADDR %s  and PORT %d to the given File descriptor",inet_ntoa(stSockaddr.sin_addr),ntohs(stSockaddr.sin_port));
   }

   printf("\n\nStill the connection is not open... Going to open the connection at specified port and going to listen " );

   int listen_status=-1;

   listen_status=listen(socketFD,1);  // vino change here
   if(listen_status == 0)
   {
      printf("\n\nListening for clients (Only 12 connections permitted at a time) ....");
   }
   else
   {
      perror("Error in listening :: ");
   }

   struct sockaddr_in remote_client;
   socklen_t  rem_client_size=sizeof(remote_client);

   while(1)
   {
      int new_client_fd=accept(socketFD,(struct sockaddr*)&remote_client,&rem_client_size);
      printf("\n\nAccepted the client %s Client Port %d ", inet_ntoa(remote_client.sin_addr),ntohs(remote_client.sin_port));
      printf("\nNew Fd allocated for the incoming client FD Id: %d",new_client_fd);

      memset(buffer,'\0',sizeof(buffer));
      sprintf(buffer,"HAI CLIENT.... I AM SERVER[%s] from PORT %d",inet_ntoa(stSockaddr.sin_addr));
      send(new_client_fd,buffer,strlen(buffer),0);
      memset(buffer,'\0',sizeof(buffer));
      recv(new_client_fd,buffer,sizeof(buffer),0);
      printf("\n%s ",buffer);
   }
   return 0;
}

