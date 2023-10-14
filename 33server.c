/*============================================================================
Name : 33server.c
Author : Deepanjali Ghosh
Description : Write a program to communicate between two machines using socket
Date: 12th Oct, 2023.
============================================================================
*/


#include <sys/types.h>  
#include <sys/socket.h> 
#include <netinet/ip.h> 
#include <stdio.h>      
#include <unistd.h>     

int main()
{
    int socketfd, connectionfd;  
    int binds;
    int listens;
    int clientsize;

    struct sockaddr_in address, client;

    ssize_t readBytes, writeBytes;
    char msg[100];

    socketfd= socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1)
    {
        perror("Error in creating socket\n");
        _exit(0);
    }
    else
    	printf("Server side socket created successfully\n");

    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_family = AF_INET;
    address.sin_port = htons(8080);

    binds= bind(socketfd ,(struct sockaddr *)&address, sizeof(address));
    if (binds == -1)
    {
        perror("Error in binding\n");
        _exit(0);
    }
    else
    printf("Binding to socket was successful\n");

    listens= listen(socketfd, 2);
    if (listens== -1)
    {
        perror("Error while trying to listen\n");
        _exit(0);
    }
    else
    printf("Ready for listening connections on a socket\n");

    clientsize = (int)sizeof(client);
    connectionfd= accept(socketfd, (struct sockaddr *)&client, &clientsize);
    if (connectionfd== -1)
        perror("Error while accepting a connection\n");
    else
    {

        writeBytes = write(connectionfd, "Hello!I'm the server!",sizeof("Hello!I'm the server!"));
        if (writeBytes == -1)
            perror("Error while writing to network via socket\n");
        else
            printf("Data has been sent to client!\n");

        readBytes = read(connectionfd,msg,sizeof(msg));
        if (readBytes == -1)
            perror("Error while reading from network via socket\n");
        else
            printf("Data from client: %s\n", msg);

        
    }

    close(connectionfd);

    close(socketfd);
    return 0;
}
/*Sample Output:
eep4558@deep4558-HP-Pavilion-Laptop-15-eg3xxx:~/sh2$ ./33server
Server side socket created successfully
Binding to socket was successful
Ready for listening connections on a socket
Data has been sent to client!
Data from client: Hello! Im the client!
*/
