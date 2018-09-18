#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <pthread.h>
#define PORTNUMBER 10010
struct serverParm
{
int connectionDesc;
};
void *serverThread(void *parmPtr)
{
   #define PARMPTR ((struct serverParm *) parmPtr)
int recievedMsgLen;
char messageBuf[1025];
/* Server thread code to deal with message processing */
printf("DEBUG: connection made, connectionDesc=%d\n",
PARMPTR->connectionDesc);
if (PARMPTR->connectionDesc < 0)
   {
printf("Accept failed\n");
return(0); /* Exit thread */
}
/* Receive messages from sender... */
while ((recievedMsgLen=read(PARMPTR->connectionDesc,messageBuf,sizeof(messageBuf)-1)) > 0)
{
recievedMsgLen[messageBuf] = '\0';
printf("Message: %s\n",messageBuf);
if (write(PARMPTR->connectionDesc,"GOT IT\0",7) < 0)
       {
perror("Server: write error");
return(0);
}
}
close(PARMPTR->connectionDesc); /* Avoid descriptor leaks */
free(PARMPTR); /* And memory leaks */
return(0); /* Exit thread */
}
int main (int argc, char const *argv[])
{
int listenDesc;
struct sockaddr_in myAddr;
struct serverParm *parmPtr;
int connectionDesc;
pthread_t threadID;
/* For testing purposes, make sure process will terminate eventually */
alarm(120); /* Terminate in 120 seconds */
/* Create socket from which to read */
  
if ((listenDesc = socket(AF_INET, SOCK_STREAM, 0)) < 0)
   {
perror("open error on socket");
exit(1);
}
/* Create "name" of socket */
myAddr.sin_family = AF_INET;
myAddr.sin_addr.s_addr = INADDR_ANY;
myAddr.sin_port = htons(PORTNUMBER);
  
if (bind(listenDesc, (struct sin_port *) &myAddr, sizeof(myAddr)) < 0) {
perror("bind error");
exit(1);
}
/* Start accepting connections.... */
/* Up to 5 requests for connections can be queued... */
listen(listenDesc,5);
while (1) /* Do forever */ {
/* Wait for a client connection */
connectionDesc = accept(listenDesc, (struct sockaddr *)&address, (socklen_t*)&addrlen));       //Accept The Arguements of Client.c
/* Create a thread to actually handle this client */
parmPtr = (struct serverParm *)malloc(sizeof(struct serverParm));
parmPtr->connectionDesc = connectionDesc;
if (pthread_create(&threadID, NULL, serverThread, (void *)parmPtr) != 0)
       {
perror("Thread create error");
close(connectionDesc);
close(listenDesc);
exit(1);
}
printf("Parent ready for another connection\n");
}
}