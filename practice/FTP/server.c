#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{

    FILE *fp;
    int s;int n;
    int client, server;
    struct sockaddr_in clientAddr, servAddr;
    int client_len = sizeof(clientAddr);
    int server_len = sizeof(servAddr);
//    char name[50],fname[50];
   char rcv[100],fileread[200];
  server =socket(AF_INET,SOCK_STREAM,0);
    if(server<0){
        printf("Error in socket creation\n");
        exit(0);
    }
    servAddr.sin_family=AF_INET;
    servAddr.sin_port=htons(2000);
    servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");



    if(bind(server,(struct sockaddr*)&servAddr,server_len)<0){
        printf("Error in binding\n");
        exit(0);
    }
    
    printf("Bidning sucess]\n");


    if(listen(server,1)<0){
        printf("Error in listening\n");
        exit(0);
    
    }
  client=accept(server,(struct sockaddr *)&clientAddr,&client_len);
  if(client<0){
        printf("Error in accepting\n");
        exit(0);
  }

    printf("Accepted\n");
    n=recv(server,rcv,100,0);
    rcv[n] = '\0';

   fp = fopen(rcv, "r");
    if (fp == NULL) {
        send(client, "error", 5, 0);
        close(client);
    } else {
        while (fgets(fileread, sizeof(fileread), fp)) {
            if (send(client, fileread, strlen(fileread), 0) < 0) {
                printf("Can't send file contents\n");
            }
            usleep(100000); // Introducing a small delay between sends
        }
        fclose(fp);
        send(client, "completed", 9, 0);
    }
    close(client);
    close(server);
    return 0;
}