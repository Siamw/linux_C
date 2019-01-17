#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include "msngr.h"

BoundedBufferType	Buf;
pthread_cond_t		NotFull;
pthread_cond_t		NotEmpty;
pthread_mutex_t		Mutex;

char msg[100];

void
Producer(void *dummy)
{
	char inputMsg[100];
	int n;

	while(1) {
		/* pthread_mutex_lock */
		if (  ( pthread_mutex_lock ( &Mutex ) ) < 0  )  {
			perror("pthread_mutex_lock");
			pthread_exit(NULL);
		}

		printf("Input: ");
		scanf("%s", inputMsg);

		if((n=strcmp(inputMsg, "quit")) == 0) {
			exit(0);
		}

		strcpy(msg, inputMsg);

		if ( ( pthread_cond_signal( &NotFull ) ) < 0  )  {
			perror("pthread_cond_signal");
			pthread_exit(NULL);
		}

		/* pthread_mutex_unlock */
		if ( ( pthread_mutex_unlock( &Mutex ) ) < 0 )  {
			perror("pthread_mutex_unlock");
			pthread_exit(NULL);
		}

	}
	
	pthread_exit(NULL);
}

void
Consumer(void *dummy)
{
	while(1) 	{
		/* pthread_mutex_lock */
		if ( ( pthread_mutex_lock( &Mutex ) ) < 0 )  {
			perror("pthread_mutex_lock");
			pthread_exit(NULL);
		}
		
		if( strcmp( msg, "quit") == 0 ) {
			exit(0);
		}

		printf("Output: ");
		sleep(1);
		puts( msg );		

		/* pthread_cond_signal */
		if ( ( pthread_cond_signal( &NotEmpty ) ) < 0 )  {
			perror("pthread_cond_signal");
			pthread_exit(NULL);
		}
		/* pthread_mutex_unlock */
		if ( ( pthread_mutex_unlock( &Mutex ) ) < 0 )  {
			perror("pthread_mutex_unlock");
			pthread_exit(NULL);
		}
	}

	pthread_exit(NULL);
}

main()
{
	pthread_t	tid1, tid2;

	/* pthread_cond_init */	
	/* 쓰레드 조건 변수 생성 */
	if ( ( pthread_cond_init( &NotFull, NULL  ) ) < 0 )  {
		perror("pthread_cond_init");
		pthread_exit(NULL);
	}
	/* pthread_cond_init */
	/* 쓰레드 조건 변수 생성 */
	if (  ( pthread_cond_init( &NotEmpty, NULL ) ) < 0 ) {
		perror("pthread_cond_init");
		pthread_exit(NULL);
	}
	/* pthread_mutex_init */
	/* 쓰레드 조건 변수 생성 */
	if ( ( pthread_mutex_init(&Mutex, NULL ) ) < 0   )  {
		perror("pthread_mutex_init");
		pthread_exit(NULL);
	}

	/* Producer 쓰레드 생성 */
	if (pthread_create(&tid1, NULL, (void *)Producer, (void *)NULL) < 0)  {
		perror("pthread_create");
		exit(1);
	}

	/* Consumer 쓰레드 생성 */
	if (pthread_create(&tid2, NULL, (void *)Consumer, (void *)NULL) < 0)  {
		perror("pthread_create");
		exit(1);
	}

	/* 쓰레드 종료 대기 */
	if (pthread_join(tid1, NULL) < 0)  {
		perror("pthread_join");
		exit(1);
	}
	if (pthread_join(tid2, NULL) < 0)  {
		perror("pthread_join");
		exit(1);
	}

	/* pthread_cond_destroy */
	if ( ( pthread_cond_destroy( &NotFull ) ) < 0)  {
		perror("pthread_cond_destroy");
	}
	/* pthread_cond_destory */
	if (  ( pthread_cond_destroy( &NotEmpty ) ) < 0 )  {
		perror("pthread_cond_destroy");
	}
	/* pthread_mutex_destroy */
	if ( ( pthread_mutex_destroy( &Mutex ) ) < 0  )  {
		perror("pthread_mutex_destroy");
	}
}
