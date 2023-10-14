/*============================================================================
Name : 28.c
Author : Deepanjali Ghosh
Description :Write a program to change the exiting message queue permission. (use msqid_ds structure
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
    struct msqid_ds msginfo;
    int msgstatus;                 

    key = ftok(".", 'E');

    if (key == -1)
    {
        perror("Error while generating key");
        _exit(0);
    }

    qid = msgget(key, IPC_CREAT | 0666);
    if (qid == -1)
    {
        perror("Error creating message queue!");
        _exit(0);
    }

    printf("The Key is: %d\n", key);
    printf("Message Queue Identifier: %d\n\n", qid);

    msgstatus = msgctl(qid, IPC_STAT, &msginfo);

    if (msgstatus == -1)
    {
        perror("Error while getting Message Queue info\n");
        _exit(0);
    }

    printf("Press enter to change the permission of the queue\n");
    getchar();

    msginfo.msg_perm.mode = 0777;

    msgstatus = msgctl(qid, IPC_SET, &msginfo);

    if (msgstatus == -1)
    {
        perror("Error while changing the permission\n");
        _exit(0);
    }
    printf("\nPermission changed\n");
    return 0;
}
/*Sample Output:
deep4558@deep4558-HP-Pavilion-Laptop-15-eg3xxx:~/sh2$ ./28
The Key is: 1158021221
Message Queue Identifier: 8

Press enter to change the permission of the queue


Permission changed
*/
