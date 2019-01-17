
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "shm.h"


main()
{
int shmid;
char *ptr, *pData;
int *pInt;


/* SHM_KEY, SHM_SIZE, SHM_MODE in shm.h */
if ((shmid = shmget(SHM_KEY, SHM_SIZE, SHM_MODE))<0/* shmget */)  {
perror("shmget");
exit(1);
}
if ((ptr=shmat(shmid,0,0))==(void*)-1 /* shmat */)  {
perror("shmat");
exit(1);
}

pInt = (int *)ptr;
pData = ptr + sizeof(int);//data를 넣어준다.
sprintf(pData, "This is a request from %d.", getpid());
*pInt = 1;//1에서 wile loop에서 빠져나올 수 있도록 함.
printf("Sent a request.....");

while ((*pInt) == 1)// 0이 될 때 까지 기다린다.
;

printf("Received reply: %s\n", pData);

/* Detach shared memory */
if (shmdt(ptr)<0/* shmdt */)  {
perror("shmdt");
exit(1);
}
}
