#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{

    FILE *fp;
    int s;
    int client, server;
    struct sockaddr_in clientAddr, servAddr;
    int client_len = sizeof(clientAddr);
    int server_len = sizeof(servAddr);
   char name[50],fname[50];
   char rcvg[200];
  client =socket(AF_INET,SOCK_STREAM,0);
    if(client<0){
        printf("Error in socket creation\n");
        exit(0);
    }
    servAddr.sin_family=AF_INET;
    servAddr.sin_port=htons(2000);
    servAddr.sin_addr.s_addr=inet_addr("127.0.0.1");

    //connecting to server
    if(connect(client ,(struct sockaddr*)&servAddr,server_len)<0){
        printf("Eroor in connecting to server");
        exit(0);
    }
    printf("Connected to server\n");

    printf("Enter the filename");
    
    scanf("%49s",name);
    printf("Enter the new file name");
    scanf("%49s",fname);
    fp=fopen(fname,"w");
    if(fp==NULL){
        printf("Error in opening file\n");
        exit(0);
    }
    send(client,name,strlen(name),0);
    while(1){
        s=recv(client,rcvg,100,0);
        if(s<0)
        {
            printf("Connection closed by server\n");
            break;
        }
        if(strcmp(rcvg,"error")==0)
        {
            printf("File is not available\n");
            fclose(fp);
            exit(1);
        }
        else if(strcmp(rcvg,"completed")==0)
        {
            printf("File transfer completed\n");
            fclose(fp);
            break;
        }
        else
        {

             fputs(rcvg,stdout);
            fprintf(fp,"%s",rcvg);
        }
    }
    close(client);



}