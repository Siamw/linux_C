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
if (shmid = shmget(SHM_KEY, SHM_SIZE, SHM_MODE)<0)  {//key를 접근번호로 하는 공유메모리 공간 할당을 커널에 요청한다. 그 때, 공유메모리를 가르키는 식별자를 shmid에 저장한다.
perror("shmget");
exit(1);
}
if ((ptr = shmat(shmid, 0, 0)) == (void *) -1)  {
//공유메모리 식별자 shmid에 공유메모리 세그먼트를 붙이기 위해 사용
perror("shmat");
exit(1);
}

pInt = (int *)ptr;
while ((*pInt) == 0)
; // 이 프로그램 하나만 돈다고 하면 계속 무한루프가 돌겠지만, 다른 프로그램이 이 값을 0이 아닌 값(1)로 바꿔준다. 의미 ; data를 썼구나 ! 이제 가져가면 되겠구나. 이런 의미이다.
//돌면서 lock.. spin lock -> busy waiting... cpu성능 까먹음->세마포어 이용하여 할 수 있다. 

pData = ptr + sizeof(int);
printf("Received request: %s.....", pData);
sprintf(pData, "This is a reply from %d.", getpid());
*pInt = 0;
printf("Replied.\n");

sleep(1); // 다른 프로세스가 사용하도록 잠시 쉬어줌,, 안하면 내가 사용할 shared memory가 갑자기 사라진 것이기 때문에 segmentation violation난다. 

/* Detach shared memory */
if (shmdt(ptr) < 0/* shmdt */)  {
perror("shmdt");
exit(1);
}

/* Remove shared memory */
if (shmctl(shmid, IPC_RMID, 0)<0)  {
perror("shmctl");
exit(1);
}
}
