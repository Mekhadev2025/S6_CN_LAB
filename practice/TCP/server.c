#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>


int main(){
     int client,server;
      struct sockaddr_in servAddr,clientAddr;

     server=socket(AF_INET,SOCK_STREAM,0);
     if(server<0){
            printf("Error in socket creation\n");
            exit(0);
     }
    servAddr.sin_family=AF_INET;
    servAddr.sin_port=htons(2000);
    servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");


     //binding 
        if(bind(server,(struct sockaddr *)&servAddr,sizeof(servAddr))<0)
        {
            printf("Error in binding\n");
            exit(0);
        }

        //binidng 
        printf("Binding success\n");
     ///listening 
     if(listen(server,5)<0)
     {
        
        printf("Error in listening\n");
        exit(0);
     }
  

    printf("Listening\n");
    int client_len=sizeof(clientAddr);
    client=accept(server,(struct sockaddr*)&clientAddr,&client_len);
    if(client<0){
        printf("Error in accepting\n");
        exit(0);
    }
    char cliMsg[200];
    if (recv(client, cliMsg, 200, 0) < 0) {
        printf("Error in receiving data\n");
        exit(0);
    }
    printf("Data received from client: %s\n", cliMsg);

    char buffer[1024];
    strcpy(buffer, "heyy this is server");
    if (send(client, buffer, strlen(buffer), 0) < 0) {
        printf("Error in sending data\n");
        exit(0);
    }
    printf("Data sent to client: %s\n", buffer);

    close(client);
    close(server);

    return 0;


}