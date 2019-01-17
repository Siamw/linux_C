#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "shm.h"
#include "semlib.c"
#include "prodcons.h"
#include <stdlib.h>

/*
   IPC 실습내용 중 sipc1.c sipc2.c를 다음과 같이 수정
   - busy waiting을 없애고, semaphore를 통해 동기화시킴
   - buisy waiting을 위해 사용했던 flag 4 bytes를 제외하고,
   shared memory 부분은 모두 데이터 전달을 위해 사용
   (Hint: Process간 동기화 이므로, System V semaphore를 사용해야 하며,
   POSIX semaphore API처럼 만든 semlib.c의 함수를 사용하면 됨)
*/
main()
{
		int shmid,semid,i,data;
		char *ptr, *pData;
		int *pInt;
		int emptySemid, fullSemid, mutexSemid;
	

		if ((shmid = shmget(SHM_KEY, SHM_SIZE, SHM_MODE)) < 0)  {
				perror("shmget");
				exit(1);
		}

		if ((ptr = shmat(shmid, 0, 0)) == (void *) -1)  {
		perror("shmat");
		exit(1);
		}
		
		pInt = (int *)ptr;
//		while ((*pInt) == 0)
//				;


		
		if ((emptySemid = semInit(EMPTY_SEM_KEY)) < 0)  {
				fprintf(stderr, "semInit failure\n");
				exit(1);
		}
		if ((fullSemid = semInit(FULL_SEM_KEY)) < 0)  {
				fprintf(stderr, "semInit failure\n");
				exit(1);
		}
		if ((mutexSemid = semInit(MUTEX_SEM_KEY)) < 0)  {
				fprintf(stderr, "semInit failure\n");
				exit(1);		}

		srand(0x8888);
		for (i = 0 ; i < NLOOPS ; i++)  {
				if (semWait(emptySemid) < 0)  {
						fprintf(stderr, "semWait failure\n");
						exit(1);
				}
				if (semWait(mutexSemid) < 0)  {
						fprintf(stderr, "semWait failure\n");
						exit(1);
				}

				pData = ptr + sizeof(int);
				printf("Received request: %s.....", pData);
				sprintf(pData, "This is a reply from %d.", getpid());
				*pInt = 0;
				printf("Replied.\n");

				sleep(1);


				if (semPost(mutexSemid) < 0)  {
						fprintf(stderr, "semPost failure\n");
						exit(1);
				}
				if (semPost(fullSemid) < 0)  {
						fprintf(stderr, "semPost failure\n");
						exit(1);
				}
		}

		

		if (semDestroy(emptySemid) < 0)  {
				fprintf(stderr, "semDestroy failure\n");
		}
		if (semDestroy(fullSemid) < 0)  {
				fprintf(stderr, "semDestroy failure\n");
		}
		if (semDestroy(mutexSemid) < 0)  {
				fprintf(stderr, "semDestroy failure\n");
		}
		if (shmctl(shmid, IPC_RMID, 0) < 0)  {
				perror("shmctl");
				exit(1);
		}
}
