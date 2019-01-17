#include <stdio.h>

#define MAX_CMD 256

void DoCmd(char *cmd)
{
	printf("Doing %s", cmd);
	sleep(1);
	printf("Done\n");
}

main()
{
	char cmd[MAX_CMD];
	int pid;

	while (1)  {
		printf("CMD> ");
		fgets(cmd, MAX_CMD, stdin);
		if (cmd[0] == 'q')
			break;

	if ((pid=fork())<0)  {//fork 
		perror("fork");//실패시
		exit(1);
	}
	else if (pid == 0)  {//부모면
		DoCmd(cmd);
		exit(0);
}
#if 0
	else  {
	wait(NULL);
	}
#endif
	}
}
