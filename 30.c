
/*============================================================================
Name : 30.c
Author : Deepanjali Ghosh
Description : Write a program to create a shared memory.
a. write some data to the shared memory
b. attach with O_RDONLY and check whether you are able to overwrite.
c. detach the shared memory
d. remove the shared memor
Date: 12th Oct, 2023.
============================================================================
*/


#include <sys/types.h>
#include <sys/ipc.h>   
#include <sys/shm.h>  
#include <unistd.h>    
#include <stdio.h>     

int main()
{
    key_t shmkey;         
    int shmid;    
    ssize_t shmsize = 22;
    char *shmptr, *rdonlyshmptr;

    shmkey = ftok(".", 'X');

    if (shmkey == -1)
    {
        perror("Error in generating key\n");
        _exit(0);
    }

    shmid= shmget(shmkey, shmsize, IPC_CREAT | 0666);

    if (shmid == -1)
    {
        perror("Error in creating Shared Memory\n");
        _exit(0);
    }
   
    shmptr= shmat(shmid, (void *)0, 0);

    if (*shmptr == -1)
    {
        perror("Error attaching address space\n");
        _exit(0);
    }

    printf("Press any key to write to  shared memory\n");
    getchar();
//30a
    sprintf(shmptr, "Hi!I am Deepa"); // Writing to the shared memory

    printf("Press enter to read from the shared memory!\n");
    getchar();

    printf("Msg received from shared memory: %s\n", shmptr); // Reading from the shared memory


    //30b

    rdonlyshmptr = shmat(shmid, (void *)0, SHM_RDONLY);
    if (*rdonlyshmptr== -1)
    {
        perror("Error while attaching address space!");
        _exit(0);
    }
    

    printf("Press any key to read from the shared memory!\n");
    getchar();

    printf("Data from shared memory: %s\n", rdonlyshmptr); // Reading from the shared memory


   //30c
    printf("Detaching pointer to shared memory!\n");
    shmdt(shmptr);       // Dettach pointer to Shared Memory
    shmdt(rdonlyshmptr); // Dettach pointer to Shared Memory
   

    //30d
    printf("Press any key to delete the shared memory!\n");
    getchar();

    
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
/*Sample Output:
deep4558@deep4558-HP-Pavilion-Laptop-15-eg3xxx:~/sh2$ ./30
Press any key to write to  shared memory
 
Press enter to read from the shared memory!

Msg received from shared memory: Hi!I am Deepa
Press any key to read from the shared memory!

Data from shared memory: Hi!I am Deepa
Detaching pointer to shared memory!
Press any key to delete the shared memory!

*/
