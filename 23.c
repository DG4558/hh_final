/*============================================================================
Name : 23.c
Author : Deepanjali Ghosh
Description :Write a program to print the maximum number of files can be opened within a process and
size of a pipe (circular buffer).
Date: 5th Oct, 2023.
============================================================================
*/




#include <unistd.h>    
#include <sys/types.h> 
#include <sys/stat.h>  
#include <stdio.h>     
#include <errno.h>     

int main()
{
    int status; 
    long maxnofiles;   
    long size;

    char *fifofile= "23-fifo";
    status = mkfifo(fifofile, S_IRWXU);

    if (!(errno == EEXIST || status != -1))
        perror("Error");
        maxnofiles = sysconf(_SC_OPEN_MAX);

        if (maxnofiles == -1)
            perror("Error");
        else
            printf("Max no of files that can be opened is: %ld\n", maxnofiles);

        size = pathconf(fifofile, _PC_PIPE_BUF);

        if (size== -1)
            perror("Error!");
        else
            printf("Max size of pipe: %ld\n", size);
     return 0;
    
}
/*Sample Output:
deep4558@deep4558-HP-Pavilion-Laptop-15-eg3xxx:~/sh2$ ./23
Max no of files that can be opened is: 1024
Max size of pipe: 4096
*/
