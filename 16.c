/*
============================================================================
Name : 16.c
Author : Deepanjali Ghosh
Description :Write a program to send and receive data from parent to child vice versa. Use two way communication
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
    int rb,wb;
    char *writebuff,*readbuff;

    pid_t cp;

    p1= pipe(fd1);
    p2= pipe(fd2);

    if (p1== -1 || p2== -1)
        perror("Error:");
    else
    {
        cp= fork();

        if (cp== -1)
            perror("Error:");
        else if (cp== 0)
        {
            
            close(fd1[1]);
            close(fd2[0]); 

            
            writebuff="Hi!I am child\n";
            wb= write(fd2[1], &writebuff, sizeof(writebuff));
    
            rb= read(fd1[0], &readbuff,sizeof(readbuff));
            printf("I am child,I inherited from parent the msg: %s\n", readbuff);
        }
        else
        {
            close(fd1[0]);
            close(fd2[1]); 

            writebuff= "I am parent\n";
            wb= write(fd1[1], &writebuff, sizeof(writebuff));
            

            rb= read(fd2[0], &readbuff,sizeof(readbuff));
           
            printf("I am parent,the child gave the msg: %s\n", readbuff);
        }
    }
    return 0;
}


/*Sample Output:
deepa@deepa-virtual-machine:~/sh2$ ./16
I am parent,the child gave the msg: Hi!I am child

I am child,I inherited from parent the msg: I am parent
*/
