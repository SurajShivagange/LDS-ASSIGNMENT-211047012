#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/shm.h>
#include<string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
int main()
{
int i;
void *shared_memory;
char buff[100];
int shmid;
int first, second, product;

shmid=shmget((key_t)2345, 1024, 0666|IPC_CREAT); //creates shared memory segment with key 2345, having size 1024 bytes. IPC_CREAT is used to create the shared segment if it does not exist. 0666 are the permisions on the shared segment
printf("Key of shared memory is %d\n",shmid);
shared_memory=shmat(shmid,NULL,0); //process attached to shared memory segment
printf("Process attached at %p\n",shared_memory); //this prints the address where the segment is attached with this process

printf("Enter first number of multiplication\n");
scanf("%d",&first);
printf("Enter second number of multiplication\n");
scanf("%d",&second);
product = first * second;

//printf("The product of two numbers is: %d\n", product);

char sproduct[15];

sprintf(sproduct, "%d", product); //typecasting

strcpy(shared_memory, sproduct); //data written to shared memory

printf("You wrote the product of %d*%d: %s\n",first, second, (char *)shared_memory);



//Reading from shared memory
printf("\n\nKey of shared memory is %d\n",shmid);
shared_memory=shmat(shmid,NULL,0); //process attached to shared memory segment
printf("Process attached at %p\n",shared_memory);
printf("Data read from shared memory is : %s\n",(char *)shared_memory);
}
