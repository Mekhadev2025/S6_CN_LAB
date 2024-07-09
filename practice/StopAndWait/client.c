#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>


int main(){
        int client,server;
        struct sockaddr_in servAddr,clientAddr;
    char buffer[1024];
    socklen_t addr;
        client=socket(AF_INET,SOCK_DGRAM,0);
        if(client<0){
                printf("Error in socket creation\n");
                exit(0);
        }
        servAddr.sin_family=AF_INET;
        servAddr.sin_port=htons(2000);
        servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");

  int packetCounter=7;
  while(packetCounter!=0){
       bzero(buffer,1024);
       sprintf(buffer,"%d",packetCounter);
       printf("Client:sending packet %s",buffer) ;
       sendto(client,buffer,strlen(buffer),0,(struct sockaddr *)&servAddr,sizeof(servAddr));
       struct timeval timeout;
       timeout.tv_sec=3;
       timeout.tv_usec=0;
       if(setsockopt(client,SOL_SOCKET,SO_RCVTIMEO,&timeout,sizeof(timeout))<0){
                printf("Error in setting timeout\n");
                exit(0);
       }
       else{
        bzero(buffer,1024);
        addr=sizeof(servAddr);
        if(recvfrom(client,buffer,1024,0,(struct sockaddr *)&servAddr,&addr)<0){
                printf("Error in receiving data\n");
                // exit(0);
        }
        else{
                printf("Client:received ack %s\n",buffer);
                packetCounter--;
        }
       }

  }
  close(client);
}