#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

void CharAtaTime(char *str)//race.c와 같다
{
	char	*ptr;
	int	c, i;

	setbuf(stdout, NULL);
	for (ptr = str ; c = *ptr++ ; )  {
		for(i = 0 ; i < 999999 ; i++)
			;
		putc(c, stdout);
	}
}

main()
{
	pid_t pid;


	if ((pid = fork()) < 0)  {
		perror("fork");
		exit(1);
	}
	else if (pid == 0)  {
		CharAtaTime("output from child\n");
	}	 
	else  {
		wait(NULL);//자식 프로세스 작업이 끝날 때 까지 대기
		CharAtaTime("output from parent\n");
	}
}
