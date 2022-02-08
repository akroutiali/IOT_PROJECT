#include "programB.h"

#define EM_SUCCESS 1
#define EM_ERROR 0

#define sock_client "/tmp/sock_programB"
int sock =-1;
char buf[500];
struct sockaddr_un client;

int createSocket()
{
   unlink(sock_client);
   sock = socket(AF_UNIX, SOCK_DGRAM, 0);
   if (sock < 0) {
      printf("Error :opening datagram socket\n");
      return EM_ERROR;
   }

   client.sun_family = AF_UNIX;
   strcpy(client.sun_path, sock_client);

   if(bind(sock, (struct sockaddr *) &client, sizeof(struct sockaddr_un))<0)
   {
      printf("Error :failed to bind socket \n");
      return EM_ERROR;
   }
   return EM_SUCCESS;
}

void threadFunc()
{
   for(;;)
   {
      if(recvfrom(sock, buf, sizeof(buf), 0, NULL, NULL)<0)
      {
         printf("No DATA received \n");
      }
      else
      {
         printf("%s \n",buf);
      }
   }
}

int main()
{
   if(!createSocket())
      return 0;
   pthread_t threadId;
   pthread_create(&threadId, NULL, &threadFunc, NULL);
   pthread_join(threadId, NULL);
   
   return 0;
}