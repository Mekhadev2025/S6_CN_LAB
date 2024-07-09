#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include<time.h>
int main()
{
    int x = 0;
    srand(time(0));
    int client, server;
    struct sockaddr_in servAddr, clientAddr;
    char buffer[1024];
    socklen_t addr;
    server = socket(AF_INET, SOCK_DGRAM, 0);
    if (server < 0)
    {
        printf("Error in socket creation\n");
        exit(0);
    }
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(2000);
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // bind
    if (bind(server, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0)
    {
        printf("Error in binding\n");
        exit(0);
    }
    printf("Binding success\n");

    while (1)
    {
        bzero(buffer, 1024);
        addr = sizeof(clientAddr);
        recvfrom(server, buffer, sizeof(buffer), 0, (struct sockaddr *)&clientAddr, &addr);

        if (atoi(buffer) != x)
        {
            printf("Server:received packet %s\n", buffer);
        }
        else
        {
            printf("Server:received  duliacte packet %s\n", buffer);
        }
        x = atoi(buffer);
        sleep(1);
        if (rand() % 2 == 0)
        {
            printf("Server:send ack %s\n", buffer);
            sendto(server, buffer, strlen(buffer), 0, (struct sockaddr *)&clientAddr, sizeof(clientAddr));
        }
    }
}