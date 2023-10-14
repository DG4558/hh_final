/*
============================================================================
Name : 15.c
Author : Deepanjali Ghosh
Description :Write a simple program to send some data from parent to the child process.
Date: 3rd Oct, 2023.
============================================================================
*/






#include <unistd.h>    
#include <sys/types.h> 
#include <stdio.h>     

int main()
{
    pid_t cp;
    int fd[2]; 
    char *readbuff,*writebuff;            
    int p;            
    int rb,wb;

    writebuff= "Hi!I am Parent\n";

    p= pipe(fd);

    if (p== -1)
        perror("Error:\n");
    else
    {
        cp= fork();
        if (cp== -1)
            perror("Error:");
        else if (cp== 0)
        {
        
            rb = read(fd[0], &readbuff, sizeof(readbuff));
            printf("Data inherited from parent: %s\n", readbuff);
        }
        else
        {
     
            wb = write(fd[1], &writebuff, sizeof(writebuff));
     
        }
    }
    return 0;
}

/*Sample Output:
deepa@deepa-virtual-machine:~/sh2$ gcc 15.c -o 15
deepa@deepa-virtual-machine:~/sh2$ ./15
Data inherited from parent: Hi!I am Parent
*/
