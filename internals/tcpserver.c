#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>


/*
server:
    * The server program listens for incoming connections from clients.
    * It receives a message from the client and sends a response.
    * The server is expected to be running on the same machine.
    * The server listens on port 6265 for incoming connections.
    * The server sends a message "Hi, This is server" to the client.
    * The server closes the connection after sending the message.
    * The server closes the listening socket after the communication is complete.

newsock:
    * The newsock variable is used to store the file descriptor of the socket returned by the accept() system call.
    * It is used to refer to the socket that is created for the accepted connection.
    * It is used to send and receive data on the accepted connection.
    * It is closed using the close() system call when the communication is complete.

sockaddr_in:
    * The sockaddr_in structure is used to store socket address information for the server.
    * It contains the address family (AF_INET), port number, and IP address of the server.
    * It is used to bind the socket to a specific port and IP address.
    * It is used to accept incoming connections from clients.
    * It is used to send data to clients.
    * It is used to receive data from clients.
sockaddr_storage:
    * The sockaddr_storage structure is used to store socket address information.
    * It is large enough to hold the socket address structure for any supported address family.
    * It is used to store the address of the client when accepting a connection.
    * It is used to store the address of the server when binding the socket.
    * It is used to store the address of the server when sending data to the client.
    * It is used to store the address of the client when receiving data from the client.
    
    
listen() :
    * The listen() system call is used to listen for incoming connections on a socket.
    * It takes two arguments:
        * The file descriptor of the socket.
        * The maximum number of pending connections that can be queued.
    * It returns 0 on success and -1 on failure.

accept():
    * The accept() system call is used to accept a connection on a socket.
    * It takes three arguments:
        * The file descriptor of the socket.
        * A pointer to a sockaddr structure where the address of the client will be stored.
        * A pointer to a socklen_t variable that stores the size of the sockaddr structure.
    * It returns a new file descriptor that can be used to refer to the accepted connection.
    * It returns -1 on failure.
*/
int main() { // Corrected the function declaration of main

    int server, newsock;
    char buffer[1024];
    struct sockaddr_in servAddr;
    struct sockaddr_storage store;
    socklen_t addrSize;

    server = socket(AF_INET, SOCK_STREAM, 0);
    if (server < 0) { // Check if socket creation failed
        perror("Socket creation failed");
        return 1;
    }

    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(6265);
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Corrected the quotation marks

    if (bind(server, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0) { // Check if binding failed
        perror("Binding failed");
        return 1;
    }

    if (listen(server, 5) < 0) { // Corrected the function name and added missing parenthesis
        perror("Listen failed");
        return 1;
    }

    printf("Listening...\n"); // Changed "Listening" to "Listening..."

    addrSize = sizeof(store);
    newsock = accept(server, (struct sockaddr *) &store, &addrSize);
    if (newsock < 0) { // Check if accept failed
        perror("Accept failed");
        return 1;
    }

    recv(newsock, buffer, 1024, 0);
    printf("2. Data received: %s\n", buffer); // Added a newline character

    strcpy(buffer, "Hi, This is server\n"); // Corrected the function name

    printf("3. Sending data to client...\n");
    send(newsock, buffer, strlen(buffer), 0); // Changed 19 to strlen(buffer)

    close(newsock);
    close(server);

    return 0; // Added return statement
}

