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
    int fd, writeBytes;
    char msg[100];

    fd= open(fifo, O_NONBLOCK | O_WRONLY);

    if (fd == -1)
    {
        perror("Error");
        _exit(0);
    }

    writeBytes = write(fd, "Hi!I am Deepa", sizeof("Hi!I am Deepa"));

    if (writeBytes == -1)
        perror("Error while writing to FIFO!");

    close(fd);
    return 0;
}
