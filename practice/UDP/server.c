#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/socket.h>



int main(){
    int client,server;
    struct sockaddr_in clientAddr,servAddr;
    int client_len=sizeof(clientAddr);

    char cliMsg[2000],servMsg[2000];

      server=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
        if(server<0){
            printf("Error in socket creation\n");
            exit(0);
        }

        printf("socket created succesffullt\n");

        servAddr.sin_family=AF_INET;
        servAddr.sin_port=htons(2002);
        servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");


       if(bind(server,(struct sockaddr *)&servAddr,sizeof(servAddr))<0){
        printf("Error in binding\n");
        exit(0);
       }


      if(recvfrom(server,cliMsg,sizeof(cliMsg),0,(struct sockaddr*)&clientAddr,&client_len)<0){
        printf("Error in receiving from client\n");
        exit(0);
      }
      printf("Message from client is %s:",cliMsg);
      strcpy(servMsg,"heyy this is server");

      if(sendto(server,servMsg,strlen(servMsg),0,(struct sockaddr *)&clientAddr,client_len)<0){
        printf("Error in sending to client\n");
        exit(0);
      }

      printf("Send to the client succesfully ");

    
return 0;

}