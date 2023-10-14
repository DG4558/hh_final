/*
============================================================================
Name : 17b.c
Author : Deepanjali Ghosh
Description :Write a program to execute ls -l | wc.
b. use dup2
Date: 3rd Oct, 2023.
============================================================================
*/
#include <unistd.h>    
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
            dup2(fd[0],0); 
            execl("/usr/bin/wc", "wc", NULL);
        }
        else
        {
            
            close(1);
            close(fd[0]);
            dup2(fd[1],1);
            
            execl("/usr/bin/ls", "ls", "-l", NULL);
        }
    }
    return 0;
}
/*Sample Output:
deepa@deepa-virtual-machine:~/sh2$ gcc 17b.c -o 17b
deepa@deepa-virtual-machine:~/sh2$ ./17b
     12     101     543
*/
