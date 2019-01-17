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

	while (1)  {
		printf("CMD> ");
		fgets(cmd, MAX_CMD, stdin);//cmd에 입력받음
		if (cmd[0] == 'q')//q입력할때까지 반복 
		break;

	DoCmd(cmd);
}
}
