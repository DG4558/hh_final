/*
============================================================================
Name : 20.c
Author : Deepanjali Ghosh
Description :Write two programs so that both can communicate by FIFO -Use one way communication.
Date: 3rd Oct, 2023.
============================================================================
*/




#include <sys/types.h> 
#include <sys/stat.h>  
#include <fcntl.h>     
#include <unistd.h>  
#include <stdio.h>    

int main()
{
    int status;                              
    char msg[] = "I am prog 1 and sending data\n";
    int fd;                                          
    int wb;                            

    status= mkfifo("myfifo",0744);

    if (status== -1){
        perror("Error:");
        return 0;
        }
    fd= open("myfifo", O_WRONLY);
  
        wb = write(fd, &msg, sizeof(msg));
        if (wb == -1)
            perror("Error:");
        close(fd);
  return 0;
    
}
