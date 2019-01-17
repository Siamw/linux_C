#include <stdio.h>
#include <signal.h>
#include <pthread.h>

pthread_t ThreadId[2];

void SigIntHandler(int signo)
{
	int i;

	printf("Received a SIGINT signal by thread %d\n", pthread_self());//
	printf("Terminate other threads: tid=%d, %d\n", ThreadId[0], ThreadId[1]);

	for (i = 0 ; i < 2 ; i++)  {
		/* Cancel execution of all threads */
		if (pthread_cancel(ThreadId[i])/* pthread_cancel */)  {//스레드들 종료
			perror("pthread_cancel");
			exit(1);
		}
	}
	for (i = 0 ; i < 2 ; i++)  {//종료 기다림
		if (pthread_join(ThreadId[i], NULL))  {
			perror("pthread_join");
			exit(1);
		}
	}

	printf("Threads terminated: tid=%d, %d\n", ThreadId[0], ThreadId[1]);
										//terminate 된 thread들
	exit(0);
}

void Thread1(void *dummy)
{
	printf("Thread %d created.....\n", pthread_self());

	if (pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL))  {
	//pthread_cancel()에 대한 호출로 인해 취소 요청을 하는지 여부를 제어
	//취소할수있게함(여러 유형 존재)
		perror("pthread_setcancelstate");
		pthread_exit(NULL);
	}
	if (pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL))  {
		//the thread can be canceled at any time
		perror("pthread_setcanceltype");
		pthread_exit(NULL);
	}

	while (1)
	;
}

void Thread2(void *dummy)
{
	printf("Thread %d created.....\n", pthread_self());
//마찬가지
	if (pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL))  {
		perror("pthread_setcancelstate");
		pthread_exit(NULL);
	}
	if (pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL))  {
		perror("pthread_setcanceltype");
		pthread_exit(NULL);
	}	

	while (1)
	;
}

main()
{
	if (pthread_create(&ThreadId[0], NULL, (void *)Thread1, NULL) < 0)  {//스레드생성
		perror("pthread_create");
		exit(1);
	}
	if (pthread_create(&ThreadId[1], NULL, (void *)Thread2, NULL) < 0)  {//스레드생성
		perror("pthread_create");
		exit(1);
	}
 
	signal(SIGINT, SigIntHandler);//handler 실행

	printf("Press ^C to quit\n");

	for ( ; ; )
	pause();
}
