#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>

/*
Steps
-----
1. Create a socket :
    - socket() function creates a new socket and returns a file descriptor referring to that socket.
    - The first argument specifies the address domain of the socket.
    - The second argument specifies the type of socket.
    - The third argument specifies the protocol to be used with the socket.
    - The protocol is 0 because there is only one protocol supported by the Internet address family.
    - The function returns a file descriptor for the new socket, or -1 if an error occurred.
2. Bind it to a port:

    - The bind() function binds the socket to the address of the current host and port number on which the server will run.
    - The first argument is the socket file descriptor, and the second is the address of the host to which the server will bind.
    - The address of the host is the structure of the sockaddr_in structure.
    - The third argument is the size of this address.
    - The function returns 0 on success and -1 if it fails.

3. Receive data from client:
    - The recvfrom() function receives data on a socket, and the function is used to receive data from a socket.
    - The first argument is the socket file descriptor, the second is a pointer to the buffer where the data will be stored,
    - the third is the number of bytes to be received, the fourth is the type of message reception.
    - The last two arguments are the address of the client socket, and the length of the client socket structure, respectively.
    - The function returns the number of bytes received.

4. Send data to client:
    - The sendto() function is used to send data to the client.
    - The first argument is the socket file descriptor, the second is the buffer containing the data to be transmitted,
    - the third is the size of the buffer, the fourth is the type of message reception.
    - The last two arguments are the address of the client socket, and the length of the client socket structure, respectively.
    - The function returns the number of bytes sent.

5. Close the socket:
    - The close() function closes the socket.
    - The first argument is the socket file descriptor of the socket to be closed.
    - The function returns 0 on success and -1 if it fails.

Terms used :
------------
socket:
    - The socket() function creates a new socket and returns a file descriptor referring to that socket.
    - The function is used to create a socket for communication.
    - The function is defined in the sys/socket.h header file.
    - The function has the following syntax:
        int socket(int domain, int type, int protocol);
    - The function takes three arguments:
        - domain: The address domain of the socket.
        - type: The type of socket.
        - protocol: The protocol to be used with the socket.
    - The function returns a file descriptor for the new socket, or -1 if an error occurred.

bind:
    - The bind() function binds the socket to the address of the current host and port number on which the server will run.
    - The function is used to bind the socket to a specific address and port number.
    - The function is defined in the sys/socket.h header file.
    - The function has the following syntax:
        int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
    - The function takes three arguments:
        - sockfd: The socket file descriptor.
        - addr: The address of the host to which the server will bind.
        - addrlen: The size of this address.
    - The function returns 0 on success and -1 if it fails.
 
recvfrom:
    - The recvfrom() function receives data on a socket, and the function is used to receive data from a socket.
    - The function is defined in the sys/socket.h header file.
    - The function has the following syntax:
        ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen);
    - The function takes six arguments:
        - sockfd: The socket file descriptor.
        - buf: A pointer to the buffer where the data will be stored.
        - len: The number of bytes to be received.
        - flags: The type of message reception.
        - src_addr: The address of the client socket.
        - addrlen: The length of the client socket structure.
    - The function returns the number of bytes received.

sendto:
    - The sendto() function is used to send data to the client.
    - The function is defined in the sys/socket.h header file.
    - The function has the following syntax:
        ssize_t sendto(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen);
    - The function takes six arguments:
        - sockfd: The socket file descriptor.
        - buf: The buffer containing the data to be transmitted.
        - len: The size of the buffer.
        - flags: The type of message reception.
        - dest_addr: The address of the client socket.
        - addrlen: The length of the client socket structure.
    - The function returns the number of bytes sent.    

close:
    - The close() function closes the socket.
    - The function is defined in the unistd.h header file.
    - The function has the following syntax:
        int close(int fd);
    - The function takes one argument:
        - fd: The socket file descriptor of the socket to be closed.
    - The function returns 0 on success and -1 if it fails.

sockaddr_in:
    - The sockaddr_in structure is used to specify a socket address in the Internet domain.
    - The structure is defined in the netinet/in.h header file.
    - The structure has the following members:
        - sin_family: Address family: AF_INET
        - sin_port: Port number
        - sin_addr: Internet address
    - The structure is used to bind the socket to a specific address and port number.


address domain:
    - The address domain specifies the address family of the socket.
    - The address domain is specified in the socket() function.
    - The address domain can be one of the following:
        - AF_INET: Address Family: Internet
        - AF_UNIX: Address Family: Unix
        - AF_ISO: Address Family: ISO
        - AF_NS: Address Family: Xerox Network Systems
        - AF_IPX: Address Family: Novell IPX
        - AF_APPLETALK: Address Family: AppleTalk
        - AF_X25: Address Family: X.25
        - AF_AX25: Address Family: AX.25
        - AF_ATMPVC: Address Family: ATM PVC
        - AF_INET6: Address Family: Internet Protocol version 6
        - AF_PACKET: Address Family: Packet
        - AF_NETLINK: Address Family: Netlink
        - AF_ROUTE: Address Family: Routing
        - AF_KEY: Address Family: Key Management
        - AF_SECURITY: Address Family: Security
        - AF_BLUETOOTH: Address Family: Bluetooth
        - AF_ALG: Address Family: Cryptographic Algorithms
        - AF_VSOCK: Address Family: Virtual Socket
        - AF_MAX: Address Family: Maximum

2002:The port number on which the server will run.
sockaddr_in: 
    - The sockaddr_in structure is used to specify a socket address in the Internet domain.
    - The structure is defined in the netinet/in.h header file.
    - The structure has the following members:
        - sin_family: Address family: AF_INET
        - sin_port: Port number
        - sin_addr: Internet address
    - The structure is used to bind the socket to a specific address and port number.

inet_addr:
    - The inet_addr() function converts the Internet host address cp from IPv4 numbers-and-dots notation into binary data in network byte order.
    - The function returns the Internet address in network byte order.
    - The function returns INADDR_NONE if the address is invalid.
    - The function returns INADDR_ANY if the address is the wildcard address.
    - The function returns INADDR_BROADCAST if the address is the broadcast address.
    - The function returns INADDR_LOOPBACK if the address is the loopback address.
    - The function returns INADDR_UNSPECIFIED if the address is unspecified.
    - The function returns INADDR_MAX_LOCAL_GROUP if the address is the maximum local group address.
127.0.0.1:
    - The IP address of the local host.
    - The address is used to bind the socket to the local host.
    - The address is used to specify the address of the server.

AF_INET stands for "Address Family: Internet". It is a constant used in socket programming to specify that the socket will be used for IPv4 addresses.
SOCK_DGRAM:
    - SOCK_DGRAM is a constant used in socket programming to specify that the socket will be used for datagram-based communication.
    - The constant is used in the socket() function to specify the type of socket.
    - The constant is used to create a socket for UDP communication.
IPPROTO_UDP:
    - IPPROTO_UDP is a constant used in socket programming to specify the UDP protocol.
    - The constant is used in the socket() function to specify the protocol to be used with the socket.
    - The constant is used to create a socket for UDP communication.

htons() function converts the unsigned short integer hostshort from host byte order to network byte order.
inet_addr() function converts the Internet host address cp from IPv4 numbers-and-dots notation into binary data in network byte order.
bind() function binds the socket to the address of the current host and port number on which the server will run.
recvfrom() function receives data on a socket, and the function is used to receive data from a socket.
sendto() function is used to send data to the client.
close() function closes the socket.


    struct sockaddr_in servAddr, client_addr :
        - servAddr: The structure of the sockaddr_in structure to bind the server socket.
        - client_addr: The structure of the sockaddr_in structure to store the client socket address.

*/

* /
    void main()
{
    int server;
    struct sockaddr_in servAddr, client_addr;
    char servMsg[2000], cliMsg[2000];
    int client_struct_length = sizeof(client_addr);

    server = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (server < 0)
    {
        printf("Error while creating socket \n");
        exit(1);
    }
    printf("Socket created successfully\n");

    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(2002);
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (bind(server, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0)
    {
        printf("Couldn't bind to the port \n");
        exit(1);
    }
    printf("Binding done\n");
    printf("Listening...\n\n");

    if (recvfrom(server, cliMsg, sizeof(cliMsg), 0, (struct sockaddr *)&client_addr, &client_struct_length) < 0)
    {
        printf("Couldn't receive\n");
        exit(1);
    }
    printf("Msg from client: %s\n", cliMsg);

    strcpy(servMsg, cliMsg); // Corrected typo from 'stropy' to 'strcpy'

    if (sendto(server, servMsg, strlen(servMsg), 0, (struct sockaddr *)&client_addr, client_struct_length) < 0)
    {
        printf("Can't send\n");
        exit(1);
    }

    close(server);
}
