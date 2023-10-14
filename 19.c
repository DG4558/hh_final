/*
============================================================================
Name : 19.c
Author : Deepanjali Ghosh
Description :Create a FIFO file by
a. mknod command
b. mkfifo command
c. use strace command to find out, which command (mknod or mkfifo) is better.
c. mknod system call
d. mkfifo library function
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
    char *mkfifoName = "./mymkfifo";    // File name of FIFO file created using `mkfifo`
    char *mknodName = "./mymknod-fifo"; // File name of FIFO file created using `mknod`

    int mkfifo_status, mknod_status; 

    // Using `mkfifo` library function
    mkfifo_status = mkfifo(mkfifoName, S_IRWXU);

    if (mkfifo_status == -1)
        perror("Error while creating FIFO file!");
    else
        printf("created FIFO file!\n");

    // Using `mknod` system call
    mkfifo_status = mknod(mknodName, __S_IFIFO | S_IRWXU, 0);

    if (mknod_status == -1)
        perror("Error while creating FIFO file!");
    else
        printf("created FIFO file. \n");
}

/*sample output:
deep4558@deep4558-HP-Pavilion-Laptop-15-eg3xxx:~/sh2$ ./19
Error while creating FIFO file!: File exists
created FIFO file. 

deep4558@deep4558-HP-Pavilion-Laptop-15-eg3xxx:~/sh2$ ./19
Succesfully created FIFO file. Check using `ll` or `ls -l` command!
Succesfully created FIFO file. Check using `ll` or `ls -l` */


