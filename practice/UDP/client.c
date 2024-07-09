#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{

    int client;
    struct sockaddr_in servAddr, clientAddr;
    char cliMsg[2000], servMsg[2000];
    int server_struct_length = sizeof(servAddr);

    // socket creation

    client = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (client < 0)
    {
        printf("Error in coket creation\n");
        exit(0);
    }
    printf("Socket created successfully\n");

    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(2002);
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Enter message to server:");

    fgets(cliMsg, sizeof(cliMsg), stdin);

    if (sendto(client, cliMsg, strlen(cliMsg), 0, (struct sockaddr *)&servAddr, server_struct_length) < 0)
    {
        printf("Unable to send message\n");
        exit(0);
    }
    printf("Message Sent succesfully");

    // receiving message

    if (recvfrom(client, servMsg, sizeof(servMsg), 0, (struct sockaddr *)&servAddr, &server_struct_length)<0)
    {
        printf("eroor in reciving from server");
        exit(0);
    }

    printf("Messgar received from server:%s", servMsg);
}