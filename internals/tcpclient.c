#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
/*
    * The client program sends a message to the server and receives a response.
    * The server is expected to be running on the same machine.

socklen_t :
    * The socklen_t type is a typedef defined in <sys/socket.h> and <sys/types.h>.
    * It is used to represent the size of the socket address structure.
    * It is an unsigned integer type.
    * It is used as the third argument to the accept(), bind(), connect(), getsockname(), getpeername(), and recvfrom() functions.
    * It is used to store the size of the socket address structure passed to these functions.
    * It is used to store the size of the socket address structure returned by these functions.
    * It is used to store the size of the socket address structure passed to the recvfrom() function.
    * It is used to store the size of the socket address structure returned by the recvfrom() function.
    * It is used to store the size of the socket address structure passed to the getsockname() function.
    * It is used to store the size of the socket address structure returned by the getsockname() function.
    * It is used to store the size of the socket address structure passed to the getpeername() function.
    * It is used to store the size of the socket address structure returned by the getpeername() function.


1.Socket creation
    * The socket() system call creates a new socket.
    * It takes three arguments:
        * The address domain of the socket (AF_INET for IPv4 addresses).
        * The type of the socket (SOCK_STREAM for TCP sockets).
        * The protocol of the socket (0 for default protocol).
    * It returns a file descriptor that can be used to refer to the socket in later function calls.
    
2. Connection:
    * The connect() system call is used to establish a connection to a remote host.
    * It takes three arguments:
        * The file descriptor of the socket.
        * A pointer to a sockaddr structure that contains the address of the remote host.
        * The size of the sockaddr structure.
    * It returns 0 on success and -1 on failure.
    
3.Sending data to server
    * The send() system call is used to send data on a connected socket.
    * It takes four arguments:
        * The file descriptor of the socket.
        * A pointer to the data to be sent.
        * The size of the data in bytes.
        * Flags (0 for default behavior).
    * It returns the number of bytes sent on success and -1 on failure.
4.Receive from server
    * The recv() system call is used to receive data from a connected socket.
    * It takes four arguments:
        * The file descriptor of the socket.
        * A pointer to a buffer where the data will be stored.
        * The size of the buffer in bytes.
        * Flags (0 for default behavior).
    * It returns the number of bytes received on success and -1 on failure.

*/ 
int main() { 
    // Corrected the function declaration of main
    int client;
    char buffer[1024];
    struct sockaddr_in servAddr;
    socklen_t addrSize;

    client = socket(AF_INET, SOCK_STREAM, 0);
    if (client < 0) { // Check if socket creation failed
        perror("Socket creation failed");
        return 1;
    }

    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(6265);
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Corrected the struct member name

    if (connect(client, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0) { // Check if connection failed
        perror("Connection failed");
        return 1;
    }

    printf("1. Sending data to server...\n"); // Corrected the newline character

    strcpy(buffer, "Hi This is client\n"); // Corrected the function name

    send(client, buffer, strlen(buffer), 0); // Changed 19 to strlen(buffer)

    recv(client, buffer, 1024, 0);
    printf("4. Data received: %s\n", buffer); // Added a newline character

    close(client);

    return 0;
}

