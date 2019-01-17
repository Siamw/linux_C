#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

main()
{
 int pid;

	if ((pid = fork()) < 0)  {//fork 발생. 값이 음수일 때 에러
	perror("fork");
	exit(1);
	}

	else if (pid == 0)  {//0이면 자식 프로세스
	/* child */
		printf("I am %d. My parent is %d.\n", getpid(), getppid());
	}
	else  {//부모프로세스
	/* parent */
	printf("I am %d. My child is %d.\n", getpid(), pid);
	}
}
