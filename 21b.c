/*============================================================================
Name : 21.c
Author : Deepanjali Ghosh
Description :Write two programs so that both can communicate by FIFO -Use two way communication.
Date: 3rd Oct, 2023.
============================================================================
*/



#include <sys/types.h> 
#include <sys/stat.h>  
#include <fcntl.h>     
#include <unistd.h>    
#include <stdio.h>     

#include "./21global.h"

int main()
{
    int readBytes, writeBytes;
    int f1, f2;
    char msg[100];

    init();

    f1 = open(f1file, O_RDONLY);
    if (f1== -1)
    {
        perror("Error");
        _exit(0);
    }

    f2 = open(f2file, O_WRONLY);
    if (f2== -1)
    {
        perror("Error while opening fifoTwo");
        _exit(0);
    }

    writeBytes = write(f2, "From 21 part 2 to 21 part 1", sizeof("From 21 part 2 to 21 part 1"));

    if (writeBytes == -1)
        perror("Error");

    close(f2);

    readBytes = read(f1, &msg, sizeof(msg));

    if (readBytes == -1)
    {
        perror("Error while reading from FIFO fifoOne!");
        _exit(0);
    }

    printf("Data from FIFO: %s\n", msg);

    close(f1);
    return 0;
}
/*Sample Output:
eep4558@deep4558-HP-Pavilion-Laptop-15-eg3xxx:~/sh2$ ./21b
Data from FIFO: From 21 part 1 to 21 part 2
*/
