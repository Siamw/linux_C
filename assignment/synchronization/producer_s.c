#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "semlib.h"
#include "prodcons.h"

main()
{
		BoundedBufferType	*pBuf;
		int	shmid, i, data;
		int	emptySemid, fullSemid, mutexSemid;

		if ((shmid = shmget(SHM_KEY, SHM_SIZE, SHM_MODE)) < 0)  {
				perror("shmget");
				exit(1);
		}
		if ((pBuf = (BoundedBufferType *)shmat(shmid, 0, 0)) == (void *) -1)  {
				perror("shmat");
				exit(1);
		}
//만듦
		if ((emptySemid = semInit(EMPTY_SEM_KEY)/* semInit */ ) < 0)  {
				fprintf(stderr, "semInit failure\n");
				exit(1);
		}
		if ((fullSemid = semInit(FULL_SEM_KEY)/* semInit */) < 0)  {
				fprintf(stderr, "semInit failure\n");
				exit(1);
		}
		if ((mutexSemid = semInit(MUTEX_SEM_KEY)/* semInit */) < 0)  {
				fprintf(stderr, "semInit failure\n");
				exit(1);
		}

		srand(0x8888);
		for (i = 0 ; i < NLOOPS ; i++)  {
				if (semWait(emptySemid)/* semWait */ < 0)  {
						fprintf(stderr, "semWait failure\n");
						exit(1);
				}
				if (semWait(mutexSemid)/* semWait */ < 0)  {
						fprintf(stderr, "semWait failure\n");
						exit(1);
				}

				printf("Producer: Producing an item.....\n");
				data = (rand()%100)*10000;
				pBuf->buf[pBuf->in].data = data;
				pBuf->in = (pBuf->in + 1) % MAX_BUF;
				pBuf->counter++;

				if (semPost(mutexSemid)/* semPost */ < 0)  {
						fprintf(stderr, "semPost failure\n");
						exit(1);
				}
				if (semPost(fullSemid)/* semPost */ < 0)  {
						fprintf(stderr, "semPost failure\n");
						exit(1);
				}
				usleep(data);
		}

		printf("Producer: Produced %d items.....\n", i);

		sleep(2);
		printf("Producer: %d items in buffer.....\n", pBuf->counter);

		if (semDestroy(emptySemid)/* semDestroy */ < 0)  {
				fprintf(stderr, "semDestroy failure\n");
		}
		if (semDestroy(fullSemid)/* semDestroy */ < 0)  {
				fprintf(stderr, "semDestroy failure\n");
		}
		if (semDestroy(mutexSemid)/* semDestroy */ < 0)  {
				fprintf(stderr, "semDestroy failure\n");
		}
		if (shmctl(shmid, IPC_RMID, 0) < 0)  {
				perror("shmctl");
				exit(1);
		}
}
