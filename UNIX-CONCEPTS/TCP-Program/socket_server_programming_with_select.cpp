
#include"stdio.h"
#include<sys/socket.h> // socket(),bind(),listen(),accept()
#include <arpa/inet.h> //inet_hton
#include<errno.h>  //Perror
#include<stdlib.h>
#include<string.h>
#include<unistd.h>  // close()

int main()
{
   int listner_fd=-1;  // here assigned to -1 because the function will return 0 if success
   int bind_status=-1;
   char buffer[100];

   printf("\nGoing to allocate resource for socket! We have passed family type,connection type,protocol name");

   listner_fd=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);

   if(listner_fd!=-1)
   {
      printf("\nSuccessfully allocated resources and created FD with id %d",listner_fd);
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

   bind_status=bind(listner_fd,(struct sockaddr *) &stSockaddr,sizeof(stSockaddr));

   if(bind_status==-1)
   {
      perror("Error in binding the socket with given socket fd and ipaddress ERR DESC:\n");
      close(listner_fd);
      exit(EXIT_FAILURE);
   }
   else
   {
      printf("\nSuccessfully binded the  IPADDR %s  and PORT %d to the given File descriptor",inet_ntoa(stSockaddr.sin_addr),ntohs(stSockaddr.sin_port));
   }

   printf("\n\nStill the connection is not open... Going to open the connection at specified port and going to listen " );

   int listen_status=-1;

   listen_status=listen(listner_fd,1);  // vino change here
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
   fd_set l_read_fd;
   fd_set l_write_fd;
   int l_max_file_descriptor=0;

   /* Initializing of fd set macro for the using select*/
   l_max_file_descriptor=listner_fd;

   FD_SET(listner_fd,&l_read_fd);   // It will add the listner_fd to l_read_fd list


   while(1)
   {
      printf("\n Blocking and selecting the FD's.....");

      /* l_max_file_descriptor+1 as first parameter because, 0 is also an fd allocated for stdin */

      if( select(l_max_file_descriptor,&l_read_fd,&l_write_fd,NULL,NULL)  <0)
      {
         perror("\nSelect Error");
      }

      for(int l_fd=3;l_fd<=l_max_file_descriptor; l_fd++ )
      {
         if(FD_ISSET(l_fd,&l_read_fd))
         {
            if(l_fd == listner_fd)
            {
               printf("\nNew client came.. Going to accept it...");
               int new_client_fd=accept(listner_fd,(struct sockaddr*)&remote_client,&rem_client_size);
               printf("\n\nAccepted the client %s Client Port %d ", inet_ntoa(remote_client.sin_addr),ntohs(remote_client.sin_port));
               printf("\nNew Fd allocated for the incoming client FD Id: %d",new_client_fd);
               printf("\n Add the new Fd to the read fd list");
               FD_SET(new_client_fd,&l_read_fd);

               if(l_max_file_descriptor < new_client_fd)
               {
                  l_max_file_descriptor = new_client_fd;
                  printf("\nNew Client came so, increased the Max file descriptor  :: %d ", l_max_file_descriptor );
               }
            }
            else
            {
               printf("\nMessage came from client which is in connection... Going to receive it");
               memset(buffer,'\0',sizeof(buffer));
               recv(l_fd,buffer,sizeof(buffer),0);
               printf("\n%s ",buffer);
               FD_CLR(l_fd,&l_read_fd);
            }
         }
      }
   }
   return 0;
}

