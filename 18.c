/*
============================================================================
Name : 18.c
Author : Deepanjali Ghosh
Description :Write a program to find out total number of directories on the pwd.
execute ls -l | grep ^d | wc ? Use only dup2.
Date: 3rd Oct, 2023.
============================================================================
*/


#include <unistd.h>    
#include <sys/types.h> 
#include <stdio.h>    

int main()
{
    int fd1[2], fd2[2];
    int p1,p2;

    pid_t c1,c2;

    p1 = pipe(fd1);
    p2 = pipe(fd2);

    if (p1 == -1 || p2==-1)
        perror("Erro:");
    else
    {
        c1= fork();

        if (c1== -1)
            perror("Error:");
        else if (c1 == 0)
        {
            close(fd2[1]); 
            close(fd1[0]);
            close(fd1[1]);

            close(0);
            dup2(fd2[0],0);

            execl("/usr/bin/wc", "wc", NULL);
        }
        else
        {
            
            c2= fork();

            if (c2== -1)
                perror("Error:");
            else if (c2== 0)
            {

                close(fd2[1]);
                close(fd1[0]);

                close(0);
                dup2(fd2[0],0);
                close(1);
                dup2(fd1[1],1);

                execl("/usr/bin/grep", "grep ^d", "^d", NULL);
            }
            else
            {
                

  
                close(fd2[0]);
                close(fd1[1]);
                close(fd1[0]);

                close(1); 
                dup2(fd2[1],1); 

                execl("/usr/bin/ls", "ls ", "-l", NULL);
            }
        }
    }
    return 0;
}


/*Sample Output:
deepa@deepa-virtual-machine:~/sh2$ ./18
      0       0       0
deepa@deepa-virtual-machine:~/sh2$ ls -l|grep ^d|wc
      0       0       0
*/
