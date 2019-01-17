#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "prodcons.h"

main()
{
BoundedBufferType	*pBuf;
int	shmid, i, data;

if ((shmid = shmget(SHM_KEY, SHM_SIZE, SHM_MODE)) < 0)  {// shared memory 생성
perror("shmget");
exit(1);
}
if ((pBuf = (BoundedBufferType *)shmat(shmid, 0, 0)) == (void *) -1)  {// shared memory attach. return point = pBuf
perror("shmat");
exit(1);
}

srand(0x8888);
for (i = 0 ; i < NLOOPS ; i++)  {
if (pBuf->counter == MAX_BUF)  {//꽉 찼는가..?
printf("Producer: Buffer full. Waiting.....\n");
while (pBuf->counter == MAX_BUF)
;
}

//꽉 차있지 않으면 무언가를 만든다.
printf("Producer: Producing an item.....\n");
data = (rand()%100)*10000;//랜덤값..
pBuf->buf[pBuf->in].data = data;
pBuf->in = (pBuf->in + 1) % MAX_BUF;
pBuf->counter++;

usleep(data);//landom data만큼 sleep. 하나 집어넣고 좀 쉴 수 있도록 함. 
}

printf("Producer: Produced %d items.....\n", i);

sleep(2);
printf("Producer: %d items in buffer.....\n", pBuf->counter);

if (shmctl(shmid, IPC_RMID, 0) < 0)  {
perror("shmctl");
exit(1);
}
}
