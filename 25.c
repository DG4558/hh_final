/*============================================================================
Name : 25.c
Author : Deepanjali Ghosh
Description :Write a program to print a message queue's (use msqid_ds and ipc_perm structures)
a. access permission
b. uid, gid
c. time of last message sent and received
d. time of last change in the message queue
d. size of the queue
f. number of messages in the queue
g. maximum number of bytes allowed
h. pid of the msgsnd and msgrcv
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
    struct msqid_ds mqinfo; 
    int msgstatus;                 

    key = ftok(".", 'D');

    if (key == -1)
    {
        perror("Error\n");
        _exit(0);
    }

    qid = msgget(key, IPC_CREAT|0666);
    if (qid == -1)
    {
        perror("Error\n");
        _exit(0);
    }

    printf("The Key is: %d\n",key);
    printf("Message Queue Identifier is: %d\n\n", qid);

    msgstatus = msgctl(qid, IPC_STAT, &mqinfo);

    if (msgstatus == -1)
    {
        perror("Error\n");
        _exit(0);
    }

    printf("Access Permission is: %od\n", mqinfo.msg_perm.mode);
    printf("UID: %d\n", mqinfo.msg_perm.uid);
    printf("GID: %d\n", mqinfo.msg_perm.gid);
    printf("Time of the last message sent: %ld\n", mqinfo.msg_stime);
    printf("Time of the last message received: %ld\n", mqinfo.msg_rtime);
    printf("Size of the  queue: %ld\n", mqinfo.__msg_cbytes);
    printf("No of messages in the queue: %ld\n", mqinfo.msg_qnum);
    printf("Max no of bytes allowed in the queue: %ld\n", mqinfo.msg_qbytes);
    printf("PID of last sent message: %d\n", mqinfo.msg_lspid);
    printf("PID of last received message: %d\n", mqinfo.msg_lrpid);
    return 0;
}
/*Sample Output:
eep4558@deep4558-HP-Pavilion-Laptop-15-eg3xxx:~/sh2$ ./25
The Key is: 1342570597
Message Queue Identifier is: 6

Access Permission is: 666d
UID: 1000
GID: 1000
Time of the last message sent: 0
Time of the last message received: 0
Size of the  queue: 0
No of messages in the queue: 0
Max no of bytes allowed in the queue: 16384
PID of last sent message: 0
PID of last received message: 0

*/

