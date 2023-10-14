/*============================================================================
Name : 22.c
Author : Deepanjali Ghosh
Description :Write a program to wait for data to be written into FIFO within 10 seconds, use select
system call with FIFO.
Date: 5th Oct, 2023.
============================================================================
*/




#include <sys/types.h>
#include <sys/stat.h>  
#include <fcntl.h>     
#include <sys/time.h>  
#include <unistd.h>   
#include <stdio.h>     

#include "./22global.h"

int main()
{
    int fd, readBytes;
    char msg[100];

    fd_set readfd;
    struct timeval timer;
    int status;

    init();

    fd= open(fifo, O_NONBLOCK | O_RDONLY);

    if (fd == -1)
    {
        perror("Error");
        _exit(0);
    }

    FD_ZERO(&readfd);
    FD_SET(fd, &readfd); 

    
    timer.tv_sec = 10;
    timer.tv_usec = 0;

   status = select(fd+ 1, &readfd, NULL, NULL, &timer);

    if (status == -1)
        perror("Error");
    else if (status)
    {
        readBytes = read(fd, &msg, sizeof(msg));

        if (readBytes == -1)
            perror("Error");
        else
            printf("Msg received : %s\n", msg);
    }
    else
        printf("Msg not received\n");

    close(fd);
    return 0;
}
/*Sample Output:
deep4558@deep4558-HP-Pavilion-Laptop-15-eg3xxx:~/sh2$ ./22a
Msg received : Hi!I am Deepa
deep4558@deep4558-HP-Pavilion-Laptop-15-eg3xxx:~/sh2$ ./22a
Msg not received*/

