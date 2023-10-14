/*============================================================================
Name : 34aclient.c
Author : Deepanjali Ghosh
Description : Write a program to create a concurrent server.
a. use fork
b. use pthread_create
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

   
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1)
    {
        perror("Error creating socket\n");
        _exit(0);
    }
    printf("Client socket created\n");

    
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_family = AF_INET;
    address.sin_port = htons(8080);

    connectstatus = connect(socketfd, (struct sockaddr *)&address, sizeof(address));
    if (connectstatus == -1)
    {
        perror("Error connecting to server\n");
        _exit(0);
    }
    printf("connection established!\n");

    

    readBytes = read(socketfd, msg, sizeof(msg));
    ;
    if (readBytes == -1)
        perror("Error reading via socket\n");
    else
        printf("Message from server: %s\n",msg);

    writeBytes = write(socketfd, "Hello I'm the client!", sizeof("Hello I'm the client!"));
    if (writeBytes == -1)
        perror("Error writing via socket!");
    else
        printf("msg sent to server\n");
    

    

    close(socketfd);
    return 0;
}
/*Sample Output:
deep4558@deep4558-HP-Pavilion-Laptop-15-eg3xxx:~/sh2$ ./34a_client
Client socket created
connection established!
Message from server: I'm the server!
msg sent to server
*/
