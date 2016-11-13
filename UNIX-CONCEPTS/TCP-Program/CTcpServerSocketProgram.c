#include"stdio.h"
#include<sys/socket.h> // socket(),bind(),listen(),accept()
#include <arpa/inet.h> //inet_hton
#include<errno.h>  //Perror 
#include<stdlib.h>
#include<string.h>
#include<unistd.h>  // close()

#define SERVER_IPADDRESS  "127.0.0.1"
#define SERVER_PORT 4557
#define EXCHANGE_BUFFER_SIZE 1024

void listenforClients(int socketFD);
int tcpServerConnectionHandling(int *socketFD,struct sockaddr_in *stSockaddr);
void handleConnection(int client_fd);
void establishConnection(int socketFD);
fd_set active_fd, read_fd_set;

int main()
{
	int socketFD=-1;
	struct sockaddr_in stSockaddr;
	memset(&stSockaddr,'\0',sizeof(stSockaddr));



	   FD_ZERO(&active_fd);    
	
	
	tcpServerConnectionHandling(&socketFD,&stSockaddr);
	listenforClients(socketFD);	     
    FD_SET(socketFD, &active_fd);   
    
            
   while(1)
   {
	   establishConnection(socketFD);    
   }
   return 0;
}



int tcpServerConnectionHandling(int *p_socketFD_ptr,struct sockaddr_in *stSockaddr)
{
	if(NULL == p_socketFD_ptr)
		return 0;
	
   int	socketFD=-1;  // here assigned to -1 because the function will return 0 if success
   int bind_status=-1;


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

   
   memset(stSockaddr,'\0',sizeof(struct sockaddr_in));
   stSockaddr->sin_family=AF_INET;
   stSockaddr->sin_port=htons(SERVER_PORT);
   stSockaddr->sin_addr.s_addr=inet_addr(SERVER_IPADDRESS);


   //Not to invoke  there

   bind_status=bind(socketFD,(struct sockaddr *) stSockaddr,sizeof(struct sockaddr));

   if(bind_status==-1)
   {
      perror("Error in binding the socket with given socket fd and ipaddress ERR DESC:\n");
      close(socketFD);
      exit(EXIT_FAILURE);
   }
   else
   {
      printf("\nSuccessfully binded the  IPADDR %s  and PORT %d to the given File descriptor",inet_ntoa(stSockaddr->sin_addr),ntohs(stSockaddr->sin_port));
   }  
   
   
   *p_socketFD_ptr=socketFD;
   
   return 1;
}

void listenforClients(int socketFD)
{
	 printf("\n\nStill the connection is not open... Going to open the connection at specified port and going to listen " ); 

   int listen_status=-1;

   listen_status=listen(socketFD,1);  // vino change here
   if(listen_status == 0)
   {
      printf("\n\nListening for clients (Only 12 connections permitted at a time) ....\n");
   }
   else
   {
      perror("Error in listening :: \n");
   }
}


void establishConnection(int socketFD)
{
	   struct sockaddr_in remote_client;
   socklen_t  rem_client_size=sizeof(remote_client);
   
		  read_fd_set = active_fd;
      
      for (int i = 0; i < FD_SETSIZE; ++i)
        {
	
        if (FD_ISSET(i, &read_fd_set))
        {	
			if(i == socketFD)
			{
				 int new_client_fd=accept(socketFD,(struct sockaddr*)&remote_client,&rem_client_size);
      printf("\n\nAccepted the client %s Client Port %d ", inet_ntoa(remote_client.sin_addr),ntohs(remote_client.sin_port));
      printf("\nNew Fd allocated for the incoming client FD Id: %d",new_client_fd); 
		FD_SET(new_client_fd, &active_fd);
				handleConnection(new_client_fd);
			}
			else
			{
				printf("\nRequest from existing client: %d",i); 				
				handleConnection(i);
			}
			
		}
	}
}

void handleConnection(int new_client_fd)
{
	  char buffer[EXCHANGE_BUFFER_SIZE];    
      memset(buffer,'\0',sizeof(buffer));     
     
      recv(new_client_fd,buffer,sizeof(buffer),0);
      printf("\n%s ",buffer);
}
