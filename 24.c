/*============================================================================
Name : 24.c
Author : Deepanjali Ghosh
Description :Write a program to create a message queue and print the key and message queue id
Date: 5th Oct, 2023.
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

    key = ftok(".", 1);

    if (key == -1)
    {
        perror("Error");
        _exit(0);
    }

    qid= msgget(key, IPC_CREAT | IPC_EXCL );
    if (qid == -1)
    {
        perror("Error\n");
        _exit(0);
    }

    printf("The Key is: %d\n",key);
    printf("The Identifier is: %d\n", qid);
    return 0;
}
/*Sample Output:
deep4558@deep4558-HP-Pavilion-Laptop-15-eg3xxx:~/sh2$ ./24
The Key is: 17170533
The Identifier is: 0
*/
