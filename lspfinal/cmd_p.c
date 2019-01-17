#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define	MAX_CMD		256

void DoCmd(char *cmd)
{
	*strchr(cmd, '\n') = '\0';
	if( execlp(cmd, cmd, NULL) < 0 ){
		perror("execlp");
		exit(1);
	}
	printf("\n");
}

int main()
{
	char	cmd[MAX_CMD];
	int		pid;

	while (1)  {
		printf("CMD> ");
		fgets(cmd, MAX_CMD, stdin);	
		if (cmd[0] == 'q')
			break;

		if ((pid = fork()) < 0)  {
			perror("fork");
			exit(1);
		}
		else if (pid == 0)  {
			DoCmd(cmd);
			exit(0);
		}
		else  {
			wait(NULL);
		}
	}

	return 0;
}
