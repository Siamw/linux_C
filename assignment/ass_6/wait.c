#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

void SigChildHandler(int signo)//핸들러 정의
{
	printf("A child killed\n");
	exit(0);
}

main()
{
	pid_t pid;
 	int status;

	if(signal(SIGCHLD, SigChildHandler)==SIG_ERR){//시그널 핸들러 설정
		perror("signal error");
		exit(1);
	}

	if ((pid = fork()) < 0)  {//fork 해서 에러나면,
		perror("fork");
		exit(1);
	}

	else if (pid == 0)  {//child면
		printf("I'm a child\n");
		sleep(2);
	}

	else {//parent면자식 프로세스가 종료할 때 까지 기다린다.가 원래 기
	
		while(1) pause();//wait 
			
		printf("A child killed with %d status\n", status);
	}

}
