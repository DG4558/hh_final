/*
============================================================================
Name : 17c.c
Author : Deepanjali Ghosh
Description :Write a program to execute ls -l | wc.
c. use fcntl
Date: 3rd Oct, 2023.
============================================================================
*/
#include <unistd.h>
#include <fcntl.h>    
#include <sys/types.h> 
#include <stdio.h>     

int main()
{
    
    int fd[2];  
    int p; 
    pid_t cp;

    p= pipe(fd);

    if (p == -1)
        perror("Error:\n");
    else
    {
        cp= fork();

        if (cp == -1)
            perror("Error :");
        else if (cp== 0)
        {
            close(0);
            close(fd[1]);
            fcntl(fd[0],F_DUPFD,0);
            execl("/usr/bin/wc", "wc", NULL);
        }
        else
        {
            
            close(1);
            close(fd[0]);
            fcntl(fd[1],F_DUPFD,1);
            
            execl("/usr/bin/ls", "ls", "-l", NULL);
        }
    }
    return 0;
   }
   
   
/*Sample Output:
deepa@deepa-virtual-machine:~/sh2$ gcc 17c.c -o 17c
deepa@deepa-virtual-machine:~/sh2$ ./17c
     14     119     641
*/
