#include <stdio.h>
#include <pthread.h>
#include "semlib2.h"


		int
sem_init(sem_t *sem, int pshared, int value)
{
		if (pshared)  {//지원을안한다 그냥 0으로 사용
				fprintf(stderr, "Function not supported\n");
				return -1;
		}

		if (pthread_mutex_init(&sem->mutex, NULL) < 0)
				return -1;

		if (pthread_cond_init(&sem->cond, NULL) < 0)
				return -1;

		sem->sval = value;//value초기화

		return 0;//성공시
}

		int
sem_wait(sem_t *sem)
{
		if (pthread_mutex_lock(&sem->mutex) < 0)//lock걸고
				return -1;

		if (sem->sval == 0)  {
				while (sem->sval == 0)  {//lock풀고
						if (pthread_cond_wait(&sem->cond, &sem->mutex) < 0)  {
								if (pthread_mutex_unlock(&sem->mutex) < 0)
										return -1;
								return -1;
						}
				}
				sem->sval--;// -1 .  critical sectino이기 때문에 lock, unlock 진행
		}
		else  {
				sem->sval--;
		}

		if (pthread_mutex_unlock(&sem->mutex) < 0)
				return -1;

		return 0;
}

		int
sem_trywait(sem_t *sem)
{
		if (pthread_mutex_lock(&sem->mutex) < 0)
				return -1;

		if (sem->sval == 0)  {//0이면 실패
				if (pthread_mutex_unlock(&sem->mutex) < 0)
						return -1;
				return -1;
		}
		else  {
				sem->sval--;
		}

		if (pthread_mutex_unlock(&sem->mutex) < 0)
				return -1;

		return 0;
}

		int
sem_post(sem_t *sem)
{
		if (pthread_mutex_lock(&sem->mutex) < 0)
				return -1;

		if (sem->sval == 0)  {//0인 경우에는 기다리는애를 깨워야한다.
				if (pthread_cond_signal(&sem->cond) < 0)  {//깨움
						if (pthread_mutex_unlock(&sem->mutex) < 0)
								return -1;
						return -1;
				}
		}

		sem->sval++;//세마포어값 1 증가

		if (pthread_mutex_unlock(&sem->mutex) < 0)
				return -1;

		return 0;
}

		int
sem_getvalue(sem_t *sem, int *sval)
{
		*sval = sem->sval;
//return 값 틀렸을수도 있음. 리턴 뭐로하는지 확인해보기 *************************
		return sval;
}

		int
sem_destroy(sem_t *sem)
{
		if (pthread_mutex_destroy(&sem->mutex) < 0)
				return -1;

		if (pthread_cond_destroy(&sem->cond) < 0)
				return -1;

		return 0;
}

