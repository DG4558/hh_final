/*
============================================================================
Name : 14.c
Author:Deepanjali Ghosh
Description:Write a simple program to create a pipe, write to the pipe, read from pipe and display on
the monitor.
Date: 3rd Oct, 2023.
============================================================================
*/



#include <unistd.h> 
#include <stdio.h>  

int main()
{
    
    int fd[2];                
    char *writebuff = "Hi"; 
    char *readbuff;
    int p;            
    int rb,wb;

    
    p= pipe(fd);

    if (p == -1)
        perror("Error:\n");
    else
    {
        printf("Writing to the pipe\n");
        wb = write(fd[1], &writebuff, sizeof(writebuff));
        if (wb == -1)
            perror("Error:\n");
        else
        {
            printf("Reading from the pipe\n");
            rb= read(fd[0], &readbuff, sizeof(readbuff));
            if (rb == -1)
                perror("Error:\n");
            else
                printf("Written in pipe: %s\n", readbuff);
        }
    }
    return 0;
   }
   /*Sample output:
deep4558@deep4558-HP-Pavilion-Laptop-15-eg3xxx:~/sh2$ ./14
Writing to the pipe
Reading from the pipe
Written in pipe: Hi*/

