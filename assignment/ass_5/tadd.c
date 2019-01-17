#include <stdio.h>
#include <pthread.h>

int Sum(void* data)  // 전달받은 min에서부터 max까지의 합을 반환하는 함수
{
	int min = ((int*)data)[0];
	int max = ((int*)data)[1];
	int total = 0;
	
	for(; min<=max; min++){
		printf("%d + %d = %d\n", total, min, total+min);
		total += min;
	}
	return total;
}

int main()
{
	pthread_t tid1, tid2;
	int data1[2] = {1, 50};
	int data2[2] = {51, 100};
	int status1, status2;
	int total;


	// 각각의 스레드를 1~50, 51~100의 매개변수를 전달하여 생성한다.
	if( pthread_create(&tid1, NULL, (void*)Sum, (void*)data1) <0 ){
		perror("pthread_create");
		exit(1);
	}
	if( pthread_create(&tid2, NULL, (void*)Sum, (void*)data2) <0 ){
		perror("pthread_create");
		exit(1);
	}
	printf("Thread created: %d, %d \n", tid1, tid2);


	// 스레드들이 종료되길 기다렸다가, 종료리턴값을 받아온다.
	if( pthread_join(tid1, (void*)&status1) < 0 ){
		perror("pthread_join");
		exit(1);
	}
	if( pthread_join(tid2, (void*)&status2) < 0 ){
		perror("pthread_join");
		exit(1);
	}
	printf("Thread terminated: %d, %d \n", status1, status2);


	// 최종 값 출력
		total = status1 + status2;
		printf("\nTotal = %d \n\n", total);

	return 0;
}


