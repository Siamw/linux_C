#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

char *EnvInit[] = { "USER=unknown", "PATH=/tmp", NULL };

main()
{

	pid_t pid;

	if ((pid = fork()) < 0)  {//fork 하고 음수면 error
		perror("fork");
		exit(1);
	}
	else if (pid == 0)  {//자식이면
		/* specify pathname, specify environment */
		/* $ /export/home/cjs/work/unix/process/env myarg1 MYARG2 */
		/* with EnvInit environment */
		if (execle("/home/lsp49/assignment/ass_5/env","env", "myarg1","MYARG2",NULL,EnvInit)<0)  {
			perror("execle");
			exit(1);
		}
	}


	if (waitpid(pid, NULL, 0) < 0)  {
		perror("waitpid");
		exit(1);
	}

	if ((pid = fork()) < 0)  {//fork 하고 음수면 error
		perror("fork");
		exit(1);
	}
	else if (pid == 0)  {//자식이면
		/* specify filename, inherit environment */
		/* $ env */
		if (execlp("env","env",NULL)<0)  {
			perror("execlp");
			exit(1);
		}
	}	

}
