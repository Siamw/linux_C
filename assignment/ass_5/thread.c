#include <stdio.h>
#include <pthread.h>


void PrintMsg(char *msg)
{
	printf("%s", msg);

	pthread_exit(NULL);
}

main()
{
	pthread_t tid1, tid2;
	char *msg1 = "Hello, ";
	char *msg2 = "World!\n";

/* Thread ID: tid1, Thread function: PrintMsg, Thread argument: msg1 */
if (pthread_create(&tid1, NULL, (void *)PrintMsg, (void *)msg1)<0)  {
//thread생성. 쓰레드 식별자, 쓰레드 특성 지정(기본 null), 분기시켜 실행할 쓰레드 함수, 앞 함수의 매개변수
perror("pthread_create");
exit(1);
}

if (pthread_create(&tid2, NULL, (void *)PrintMsg, (void *)msg2) < 0)  {//마찬가지
perror("pthread_create");
exit(1);
}

printf("Threads created: tid=%d, %d\n", tid1, tid2);

/* Wait for tid1 to exit */
if (pthread_join(tid1,NULL)<0)  {//tid1이 종료되는걸 기다림. 리턴값null
perror("pthread_join");
exit(1);
}
if (pthread_join(tid2, NULL) < 0)  {//마찬가지
perror("pthread_join");
exit(1);
}

printf("Threads terminated: tid=%d, %d\n", tid1, tid2);
}
