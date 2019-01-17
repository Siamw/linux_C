#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "shm.h"
#include "prodcons.h"
#include "semlib.c"

main()
{
		int shmid,i,data;
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
		pData = ptr + sizeof(int);
		sprintf(pData, "This is a request from %d.", getpid());
		*pInt = 1;
		printf("Sent a request.....");

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
				exit(1);
		}

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

				if (semPost(mutexSemid) < 0)  {
						fprintf(stderr, "semPost failure\n");
						exit(1);
				}
				if (semPost(fullSemid) < 0)  {
						fprintf(stderr, "semPost failure\n");
						exit(1);
				}
				usleep(data);
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
		printf("Received reply: %s\n", pData);
}
