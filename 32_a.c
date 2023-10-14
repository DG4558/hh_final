/*============================================================================
Name : 32a.c
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
    char *ticketFile = "dd.txt";

    int fd;            
    ssize_t readBytes, writeBytes;
    off_t lseekoffset;
    int data;

    key_t key;      
    int sid;
    int semstatus;
    int semopstatus;

    fd = open(ticketFile,O_CREAT|O_RDWR);
    if (fd == -1)
    {
        perror("Error opening the file\n");
        _exit(0);
    }

   
    union semun
    {
        int val;           
        struct semid_ds *buf;  
        unsigned short *array;
        struct seminfo *__buf;
    } sem;

    key = ftok(".", 'G');
    if (key == -1)
    {
        perror("Error in computing key\n");
        _exit(1);
    }

    sid= semget(key, 1, 0);
    if (sid== -1)
    {
        sid= semget(key, 1, IPC_CREAT | 0666);
        if (sid == -1)
        {
            perror("Error while creating semaphore\n");
            _exit(1);
        }

        sem.val = 1; 
        semstatus = semctl(sid, 0, SETVAL, sem);
        if (semstatus == -1)
        {
            perror("Error while initializing a binary sempahore\n");
            _exit(1);
        }
    }

    struct sembuf semOp;
    semOp.sem_num = 0;
    semOp.sem_flg = 0;

    printf("Press enter to obtain lock on the critical section\n");
    getchar();
    semOp.sem_op = -1;
    semopstatus = semop(sid, &semOp, 1);
    if (semopstatus == -1)
    {
        perror("Error while operating on semaphore\n");
        _exit(1);
    }
    
    printf("Obtained lock on critical section\n");
    printf("Now entering critical section\n");
   

    readBytes = read(fd, &data, sizeof(data));
    //printf("\nData Read is %d\n",data);
    if (readBytes == -1)
    {
        perror("Error while reading from ticket file!");
        _exit(0);
    }
    else if (readBytes == 0)
        data = 1;
    else
    {
        data += 1;
        lseekoffset = lseek(fd, 0, SEEK_SET);
        if (lseekoffset == -1)
        {
            perror("Error while seeking\n");
            _exit(0);
        }
    }

    writeBytes = write(fd, &data, sizeof(data));
    if (writeBytes == -1)
    {
        perror("Error while writing to ticket file!");
        _exit(1);
    }

   // printf("Your ticker number is - %d\n", data);

    printf("Press enter to exit from critical section\n");
    getchar();

    

  
    semOp.sem_op = 1;
    semopstatus = semop(sid, &semOp, 1);
    if (semopstatus == -1)
    {
        perror("Error while operating on semaphore!");
        _exit(1);
    }
    close(fd);
    return 0;
}
/*Sample Output:
deep4558@deep4558-HP-Pavilion-Laptop-15-eg3xxx:~/sh2$ ./32_a
Press enter to obtain lock on the critical section

Obtained lock on critical section
Now entering critical section
Press enter to exit from critical section*/

