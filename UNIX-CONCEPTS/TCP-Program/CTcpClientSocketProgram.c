#include"stdio.h"
#include<sys/socket.h> // socket(),bind(),listen(),accept()
#include <arpa/inet.h> //inet_hton
#include<errno.h>  //Perror
#include<stdlib.h>
#include<string.h>
#include<unistd.h>  // close()
#include <netinet/in.h>


#define SERVER_IPADDRESS  "127.0.0.1"
#define SERVER_PORT 4557
#define EXCHANGE_BUFFER_SIZE 1024

void handleConnection(int connection_fd);
int tcpClientConnectionHandling(int *p_connectionFdPtr);


int main()
{
   int connection_fd=-1;  // here assigned to -1 because the function will return 0 if success
   tcpClientConnectionHandling(&connection_fd);
   
   handleConnection(connection_fd);
  
   return 0;
}

int tcpClientConnectionHandling(int *p_connectionFdPtr)
{
	int connection_fd=-1;  // here assigned to -1 because the function will return 0 if success


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
   stSockaddr.sin_port=htons(SERVER_PORT);
   stSockaddr.sin_addr.s_addr=inet_addr(SERVER_IPADDRESS);


   printf("\nConnecting to server for acceptance...");

   if(connect(connection_fd,(struct sockaddr *)&stSockaddr,sizeof(const struct sockaddr)) < 0)
   {
      perror("Unable to connet server.. ");
      exit(-1);
   }

	*p_connectionFdPtr=connection_fd;
   printf("\n Connected with server succesfully !!!");	   
   
   return 1;
}


void handleConnection(int connection_fd)
{
	 /* Send the handshake message to server */
	 
	 char buffer[EXCHANGE_BUFFER_SIZE];
	   memset(buffer,'\0',sizeof(buffer));
   strcpy(buffer,"Hai Server... I am your client. How are you?");
   if(send(connection_fd,buffer,sizeof(buffer),0) < 0)
   {
      perror("Send Error");
   }
}

