#include <stdio.h>
#include "semlib.h"


int
semInit(key_t key) // make semaphore
{
		int     semid;

		if ((semid = semget(key, 1, 0600 | IPC_CREAT)) < 0)  {//make 1. only me
				perror("semget");
				return -1;
		}

		return semid;
}

int
semInitValue(int semid, int value)//semid에 value값 초기화
{
		union semun {
				int     val;
		} semun;

		semun.val = value;
		if (semctl(semid, 0, SETVAL, semun) < 0)  {//set value 로 값 초기화
				perror("semctl");
				return -1;
		}

		return semid;
}

int
semWait(int semid)
{
		struct sembuf   semcmd;

		semcmd.sem_num = 0;
		semcmd.sem_op = -1;//wait : -1
		semcmd.sem_flg = SEM_UNDO;
		if (semop(semid, &semcmd, 1) < 0)  {
				perror("semop");
				return -1;
		}

		return 0;
}

int
semTryWait(int semid)
{
		struct sembuf   semcmd;

		semcmd.sem_num = 0;
		semcmd.sem_op = -1;
		semcmd.sem_flg = IPC_NOWAIT | SEM_UNDO;
		if (semop(semid, &semcmd, 1) < 0)  {
				perror("semop");
				return -1;
		}

		return 0;
}

int
semPost(int semid)//signal. +1
{
		struct sembuf   semcmd;

		semcmd.sem_num = 0;
		semcmd.sem_op = 1;//+1
		semcmd.sem_flg = SEM_UNDO;//다쓰고반납
		if (semop(semid, &semcmd, 1) < 0)  {
				perror("semop");
				return -1;
		}

		return 0;
}

int
semGetValue(int semid)
{
		union semun {
				int     val;
		} dummy;

		return semctl(semid, 0, GETVAL, dummy);//현재값 리턴
}

int
semDestroy(int semid)
{
		union semun {
				int     val;
		} dummy;

		if (semctl(semid, 0, IPC_RMID, dummy) < 0)  {//없앤다
				perror("semctl");
				return -1;
		}
		close(semid);

		return 0;
}
