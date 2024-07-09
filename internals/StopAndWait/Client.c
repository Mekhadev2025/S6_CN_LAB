#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <pthread.h>
#define TIMEOUT_VALUE 5
void main() {
char *ip = "127.0.0.1"; // Corrected IP address to localhost
int port = 5579;
int sockfd;
struct sockaddr_in addr;
char buffer[1024];
socklen_t addr_size;
// Create socket
sockfd = socket(AF_INET, SOCK_DGRAM, 0);
if (sockfd < 0) {
perror("[-] Socket error ");
exit(1);
}
// Initialize server address
memset(&addr, 0, sizeof(addr)); // Corrected memset call
addr.sin_family = AF_INET;

addr.sin_port = htons(port);
addr.sin_addr.s_addr = inet_addr(ip);
int packetCounter = 1;
while (packetCounter <= 7) {
bzero(buffer, 1024);
sprintf(buffer, "%d", packetCounter);
printf("Client: Sending packet %s\n", buffer);
sendto(sockfd, buffer, 1024, 0, (struct sockaddr *)&addr, sizeof(addr));

// Set socket timeout
struct timeval timeout;
timeout.tv_sec = TIMEOUT_VALUE;
timeout.tv_usec = 0;
if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0) {
perror("Error setting socket options");
} else {
bzero(buffer, 1024);
addr_size = sizeof(addr);
int rec = recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr *)&addr, &addr_size);
if (rec < 0) {
printf("Client: Timeout error! Sending packet again\n");
} else {
printf("Client: Received acknowledgement for packet %s\n", buffer);
packetCounter++;
}
}
sleep(1);
}
close(sockfd);
}