/*============================================================================
Name : 29.c
Author : Deepanjali Ghosh
Description :Write a program to remove the message queue
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
    key_t key;     
    int qid; 
    int msgstatus;    

    key = ftok(".", 'E');

    if (key == -1)
    {
        perror("Error while generating the key\n");
        _exit(0);
    }

    qid = msgget(key, IPC_CREAT | 0666);
    if (qid == -1)
    {
        perror("Error while creating Message Queue!");
        _exit(0);
    }

    printf("Key: %d\n", key);
    printf("Msg queue Identifier: %d\n", qid);

    msgstatus = msgctl(qid, IPC_RMID, NULL);

    if (msgstatus == -1)
    {
        perror("Error while removing Message Queue");
        _exit(0);
    }
    printf("\nMsg queue removed\n");
    return 0;
}
/*Sample output:
deep4558@deep4558-HP-Pavilion-Laptop-15-eg3xxx:~/sh2$ ./29
Key: 1158021221
Msg queue Identifier: 8

Msg queue removed
*/
