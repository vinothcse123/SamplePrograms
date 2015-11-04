#include"stdio.h"
#include<sys/socket.h> // socket(),bind(),listen(),accept()
#include <arpa/inet.h> //inet_hton
#include<errno.h>  //Perror
#include<stdlib.h>
#include<string.h>
#include<unistd.h>  // close()

int main()
{
   int connection_fd=-1;  // here assigned to -1 because the function will return 0 if success
   char buffer[100];

   printf("\nGoing to allocate resource for socket! We have passed family type,connection type,protocol name");

   connection_fd=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);


   if(connection_fd!=-1)
   {
      printf("\nSuccessfully allocated resources and created FD with id %d",connection_fd);
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


   printf("\nConnecting to server for acceptance...");

   if(connect(connection_fd,(sockaddr*)&stSockaddr,sizeof(const sockaddr)) < 0)
   {
      perror("Unable to connet server.. ");
      exit(-1);
   }

   printf("\n Connected with server succesfully !!!");

   /* Send the handshake message to server */

   memset(buffer,'\0',sizeof(buffer));
   strcpy(buffer,"Hai Server... I am your client. How are you?");
   if(send(connection_fd,buffer,sizeof(buffer),0) < 0)
   {
      perror("Send Error");
   }


   return 0;
}

