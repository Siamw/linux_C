#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

main()
{
	pid_t pid;
	int status;

	if ((pid = fork()) < 0)  {//fork를 진행하고, 음수면 에러
		perror("fork");
		exit(1);
	}
	else if (pid == 0)  {//child면
		printf("I'm a child\n");
		sleep(2);//쉼
	}
	else  {//parent면 자식프로세스가 종료할 때 까지 기다린다.
	/* wait */
	wait(&status);//status에 자식 프로세스의 상태를 받아온다. ( 자식프로세스 종료값 * 256 )
	printf("A child killed with %d status\n", status);
	}
}
