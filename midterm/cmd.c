#include <stdio.h>

#define MAX_CMD 256

main()
{
	char cmd[MAX_CMD];
	int pid;

	while (1)  {
		printf("CMD> ");
		fgets(cmd, MAX_CMD, stdin);//cmd에 입력받는다.
		if (cmd[0] == 'q')//q면 종료
			break;

	if ((pid=fork())<0)  {//fork 
		perror("fork");//실패시
		exit(1);
	}
	else if (pid == 0)  {//부모면
		wait(NULL);//자식프로세스 끝날 때 까지 기다린다.
		exit(0);
	}
	else  {
		system(cmd);//cmd에 입력받은 명령어를 실행한다.
	}
	}
}
