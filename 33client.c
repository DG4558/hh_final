/*============================================================================
Name : 33client.c
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
    int socketfd;
    int connectstatus;

    struct sockaddr_in address;

    ssize_t readBytes, writeBytes;
    char msg[100];

    socketfd= socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd== -1)
    {
        perror("Error in creating socket\n");
        _exit(0);
    }
    else
    printf("Client side socket created successfully\n");

    
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_family = AF_INET;
    address.sin_port = htons(8080);

    connectstatus = connect(socketfd, (struct sockaddr *)&address, sizeof(address));
    if (connectstatus == -1)
    {
        perror("Error while connecting to server\n");
        _exit(0);
    }
    else
    printf("Client to server connection established sucessfully\n");

    

    readBytes = read(socketfd,msg,sizeof(msg));;
    ;
    if (readBytes == -1)
        perror("Error while reading from network via socket\n");
    else
        printf("Data from server: %s\n",msg);

    writeBytes = write(socketfd, "Hello! Im the client!", sizeof("Hello! Im the client!"));
    if (writeBytes == -1)
        perror("Error while writing to network via socket\n");
    else
        printf("Data has been sent to server\n");

    close(socketfd);
    return 0;
}
/*Sample Output:
deep4558@deep4558-HP-Pavilion-Laptop-15-eg3xxx:~/sh2$ ./33client
Client side socket created successfully
Client to server connection established sucessfully
Data from server: Hello!I'm the server!
Data has been sent to server*/

