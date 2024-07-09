#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>


int main(){
     int client,server;
      struct sockaddr_in servAddr,clientAddr;

     client=socket(AF_INET,SOCK_STREAM,0);
     if(client<0){
            printf("Error in socket creation\n");
            exit(0);
     }
    servAddr.sin_family=AF_INET;
    servAddr.sin_port=htons(2000);
    servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");

    //connect to the serer

    if(connect(client,(struct sockaddr*)&servAddr,sizeof(servAddr))<0){
        printf("Error in connection\n");
        exit(0);
    }
  
  printf("Connect to server");
  char buffer[1024];
  strcpy(buffer,"heyy this is client");
  if(send(client,buffer,strlen(buffer),0)<0){
        printf("Error in sending data\n");
        exit(0);
  }
    printf("Data sent to server\n");
    char servMsg[200];
    if(recv(client,servMsg,200,0)<0){
        printf("Error in receiving data\n");
        exit(0);
    }
  
    printf("Data received from server: %s\n",servMsg);

    close(client);




}