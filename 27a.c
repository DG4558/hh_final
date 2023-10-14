/*============================================================================
Name : 27a.c
Author : Deepanjali Ghosh
Description :Write a program to receive messages from the message queue.
a. with 0 as a flag
b. with IPC_NOWAIT as a flag
Date: 12th Oct, 2023.
============================================================================
*/




#include <sys/types.h>
#include <sys/ipc.h>   
#include <sys/msg.h>   
#include <stdio.h>    
#include <unistd.h>    

int main()
{
    key_t queueKey;      
    int queueIdentifier;
    ssize_t messageSize; 

    struct msgbuf
    {
        long mtype;    
        int num; 
    } data;

    queueKey = ftok(".", 'E');

    if (queueKey == -1)
    {
        perror("Error while computing key!");
        _exit(0);
    }

    queueIdentifier = msgget(queueKey, IPC_CREAT|0666);

    if (queueIdentifier == -1)
    {
        perror("Error while creating message queue!");
        _exit(0);
    }

    data.mtype = 1;
    data.num = 1;

    messageSize = msgrcv(queueIdentifier, &data, sizeof(data), data.mtype, 0);

    if (messageSize == -1)
    {
        perror("Error while receiving msg via Message Queue!");
        _exit(0);
    }

    printf("Received number: %d\n", data.num);
    return 0;
}
/*Sample output:
deep4558@deep4558-HP-Pavilion-Laptop-15-eg3xxx:~/sh2$ gcc 27a.c -o 27a
deep4558@deep4558-HP-Pavilion-Laptop-15-eg3xxx:~/sh2$ ./27a
Received number: 100
*/
