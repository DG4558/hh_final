/*============================================================================
Name : 26.c
Author : Deepanjali Ghosh
Description :Write a program to send messages to the message queue. Check $ipcs -q
Date: 7th Oct, 2023.
============================================================================
*/





#include <sys/types.h> 
#include <sys/ipc.h>   
#include <sys/msg.h>  
#include <stdio.h>   
#include <unistd.h>    
#include <errno.h>     

int main()
{
    key_t key;        
    int qid;
    int msgstatus;

    struct msgbuf
    {
        long mtype;     
        int num;
    }msg;

   key = ftok(".", 'E');

    if (key == -1)
    {
        perror("Error");
        _exit(0);
    }

    qid = msgget(key, IPC_CREAT|0666);

    if (qid == -1)
    {
        perror("Error getting msg\n");
        _exit(0);
    }

    msg.mtype = 1;
    msg.num = 100;

    msgstatus = msgsnd(qid, &msg, sizeof(msg), 0);
    if(msgstatus==-1)
    	perror("Error sending msg\n");

    printf("Message sent\n");
    return 0;
}
/*Sample output:
deep4558@deep4558-HP-Pavilion-Laptop-15-eg3xxx:~/sh2$ ./26
Message sent
*/
