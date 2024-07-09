#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <errno.h>
#define PORT 8094
#define BUFFER_SIZE 1024
#define TIMEOUT_SEC 2
int main() {
int client_socket;
int window_size;
int num_frames;
struct sockaddr_in server_addr;
char buffer[BUFFER_SIZE];
int base = 1;
int next_seqnum = 1;
client_socket = socket(AF_INET, SOCK_STREAM, 0);
if (client_socket == -1) {
perror("Error creating socket");
exit(EXIT_FAILURE);
}
server_addr.sin_family = AF_INET;
server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
server_addr.sin_port = htons(PORT);
if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
perror("Error connecting to server");
exit(EXIT_FAILURE);
}
printf("Enter Window Size: ");
scanf("%d", &window_size);
printf("Enter Number of Frames to Send: ");
scanf("%d", &num_frames);
while (base <= num_frames) {
for (int i = next_seqnum; i < base + window_size && i <= num_frames; i++) {
sprintf(buffer, "SEQ%d", i);
printf("Sending frame: %s\n", buffer);
send(client_socket, buffer, strlen(buffer), 0);
next_seqnum++;
}
struct timeval timeout;
timeout.tv_sec = TIMEOUT_SEC;
timeout.tv_usec = 0;
if (setsockopt(client_socket, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout)) < 0) {
perror("Error setting timeout");
exit(EXIT_FAILURE);
}
memset(buffer, 0, BUFFER_SIZE);
int bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
if (bytes_received > 0 && strncmp(buffer, "ACK", 3) == 0) {
int ack_num;
sscanf(buffer, "ACK%d", &ack_num);
printf("Received acknowledgment for frame: SEQ%d\n", ack_num);
if (ack_num == base) {
base++;
next_seqnum = base + window_size;
if (next_seqnum > num_frames) {
next_seqnum = num_frames + 1;
}
}
} else {
printf("Timeout or acknowledgment not received. Retransmitting frames in window...\n");
next_seqnum = base;
}
}
close(client_socket);
return 0;
}