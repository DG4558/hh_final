/*============================================================================
Name : 31b.c
Author : Deepanjali Ghosh
Description : Write a program to create a semaphore and initialize value to the semaphore.
a. create a binary semaphore
b. create a counting semaphore
Date: 12th Oct, 2023.
============================================================================
*/





#include <sys/types.h>
#include <sys/ipc.h>   
#include <sys/sem.h>   
#include <unistd.h>   
#include <stdio.h>    

int main()
{
    key_t key;
    int sid;
    int sstatus;

    union semun {
        int val;
    } sem;

    key = ftok(".", 2);
    if (key == -1)
    {
        perror("Error in generating key\n");
        _exit(0);
    }

    sid= semget(key, 1, IPC_CREAT | 0666);

    if(sid == -1) {
        perror("Error in creating semaphore\n");
        _exit(0);
    }

    sem.val =5;

    sstatus = semctl(sid, 0, SETVAL, sem);

    if(sstatus == -1) {
        perror("Error while initalizing semaphore!");
        _exit(0);
    }
    printf("\nSempahore created and initialized sucessfully\n");
    return 0;
}
/*Sample Output:
deep4558@deep4558-HP-Pavilion-Laptop-15-eg3xxx:~/sh2$ ./31b

Sempahore created and initialized sucessfully*/

