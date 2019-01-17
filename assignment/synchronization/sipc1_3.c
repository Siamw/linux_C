#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "shm.h"

/*
   IPC 실습내용 중 sipc1.c sipc2.c를 다음과 같이 수정
   - Multi-thread version으로 변경
   - 이때, shared memory를 없애고, 전역변수로 설정
   - 전역변수로 메시지를 주고 받을때, mutex로 critical section을 보호하고,
   busy-waiting을 없애기 위해 condition variable을 사용


*/
main()
{
		int shmid;
		char *ptr, *pData;
		int *pInt;


		if ((shmid = shmget(SHM_KEY, SHM_SIZE, SHM_MODE)) < 0)  {
				perror("shmget");
				exit(1);
		}
		if ((ptr = shmat(shmid, 0, 0)) == (void *) -1)  {
				perror("shmat");
				exit(1);
		}

		pInt = (int *)ptr;
		while ((*pInt) == 0)
				;

		pData = ptr + sizeof(int);
		printf("Received request: %s.....", pData);
		sprintf(pData, "This is a reply from %d.", getpid());
		*pInt = 0;
		printf("Replied.\n");

		sleep(1);

		if (shmctl(shmid, IPC_RMID, 0) < 0)  {
				perror("shmctl");
				exit(1);
		}
}
