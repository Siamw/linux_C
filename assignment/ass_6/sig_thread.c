#include <stdio.h>
#include <signal.h>
#include <pthread.h>

#define THREAD_MAIN

#define THREAD_1
#define THREAD_2



void SigIntHandler(int signo)//handler
{
printf("Received a SIGINT signal by thread %d\n", pthread_self());
//어떤 thread에서 signal이 왔는지 출력

printf("Terminate this process\n");
exit(0);
}

void Thread1(void *dummy)
{
#ifdef THREAD_1//정의되어있다면
	signal(SIGINT, SigIntHandler);
#endif

while (1)
;
}

void Thread2(void *dummy)
{
#ifdef THREAD_2//정의되어있다면
signal(SIGINT, SigIntHandler);
#endif

while (1)
;
}

main()
{
//signal이라는건 프로세스에게 가는 것이다. 스레드가 여러개가 있으면 어떤 스레드가 처리하는지 다 다를 수 있다.. 세번 컴파일 해도 다 main thread가 할 것이다. 라는걸 확인하는 코
pthread_t tid1, tid2;

if (pthread_create(&tid1, NULL, (void *)Thread1, NULL) < 0)  {//tread1 을 arg로 하며 생
 perror("pthread_create");
 exit(1);
}

if (pthread_create(&tid2, NULL, (void *)Thread2, NULL) < 0)  {//thread2 를 arg로 하며 생성
 perror("pthread_create");
 exit(1);
}

printf("Create two threads: tid1=%d, tid2=%d\n", tid1, tid2);//만든 두개의 스레드 
printf("Main thread: tid=%d\n", pthread_self());//이건 메인스레드

#ifdef THREAD_MAIN//정의되어있다면
signal(SIGINT, SigIntHandler);
#endif

printf("Press ^C to quit\n");

for ( ; ; )
pause();
}

