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
    int fd;
    int rb;               
    char msg[200];              

    fd = open("myfifo", O_RDONLY);

    if (fd == -1)
        perror("Error while opening the FIFO file\n");
    else
    {
        rb = read(fd,&msg,sizeof(msg));
        if (rb== -1)
            perror("Error while reading from the FIFO file\n");
        else
        
        
            printf("Data read---- %s\n", msg);
        
        close(fd);
    }
    return 0;
}

/*Sample ouput:
deep4558@deep4558-HP-Pavilion-Laptop-15-eg3xxx:~/sh2$ ./20_2
Data read---- I am prog 1 and sending data*/

