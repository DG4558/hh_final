/*============================================================================
Name : 32c.c
Author : Deepanjali Ghosh
Description : Write a program to implement semaphore to protect any critical section.
a. rewrite the ticket number creation program using semaphore
b. protect shared memory from concurrent write access
c. protect multiple pseudo resources ( may be two) using counting semaphore
d. remove the created semaphore
Date: 12th Oct, 2023.
============================================================================
*/



#include <sys/ipc.h>   
#include <sys/sem.h>   
#include <sys/types.h> 
#include <sys/stat.h>  
#include <fcntl.h>   
#include <unistd.h>    
#include <stdio.h>     

int main()
{
    char *filename = "32.txt";

    int fd;           
    ssize_t readBytes; 
    off_t lseekOffset;
    char data[1000]; 

    key_t semKey;      
    int semid; 
    int semctlStatus; 
    int semopStatus;  

    
    fd = open(filename, O_CREAT|O_RDONLY);
    if (fd == -1)
    {
        perror("Error while creating the ticket file\n");
        _exit(0);
    }

   
    union semun
    {
        int val;              
    } semSet;

    semKey = ftok(".", 'Z');
    if (semKey == -1)
    {
        perror("Error while computing key!");
        _exit(1);
    }

    semid= semget(semKey, 1, 0);
    if (semid == -1)
    {
        semid= semget(semKey, 1, IPC_CREAT | 0700);
        if (semid== -1)
        {
            perror("Error while creating semaphore!");
            _exit(1);
        }

        semSet.val = 2; 
        semctlStatus = semctl(semid, 0, SETVAL, semSet);
        if (semctlStatus == -1)
        {
            perror("Error while initializing a binary sempahore!");
            _exit(1);
        }
    }

    struct sembuf semOp; 
    semOp.sem_num = 0;
    semOp.sem_flg = IPC_NOWAIT;

    printf("Press enter to obtain lock for the critical section!\n");
    getchar();

    
    semOp.sem_op = -1;
    semopStatus = semop(semid, &semOp, 1);
    if (semopStatus == -1)
    {
        perror("Error while operating on semaphore!");
        _exit(1);
    }

    printf("Obtained lock on critical section!");

    printf("Now entering critical section!");

   

    readBytes = read(fd, &data, 1000);
    if (readBytes == -1)
    {
        perror("Error while reading from sample file!");
        _exit(0);
    }
    else if (readBytes == 0) 
        printf("No data exists!\n");
    else
        printf("Sample data: \n %s", data);

    printf("\n\nPress enter key to exit critical section!\n");
    getchar();

 
    semOp.sem_op = 1;
    semopStatus = semop(semid, &semOp, 1);
    if (semopStatus == -1)
    {
        perror("Error while operating on semaphore!");
        _exit(1);
    }

    close(fd);
    return 0;
}
/*Sample Output:
deep4558@deep4558-HP-Pavilion-Laptop-15-eg3xxx:~/sh2$ gcc 32_c.c -o 32_c
deep4558@deep4558-HP-Pavilion-Laptop-15-eg3xxx:~/sh2$ ./32_c
Press enter to obtain lock for the critical section!

Obtained lock on critical section!Now entering critical section!Sample data: 
 1
2



Press enter key to exit critical section!*/


