#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void CharAtaTime(char *str)
{
	char*ptr;
	int c, i;

	setbuf(stdout, NULL);//stdout에 NUlL
	for (ptr = str ; c = *ptr++ ; )  {//ptr에 파라미터 str을 넣고, ptr 한칸씩 움직이며 c에 넣는다.
		for(i = 0 ; i < 999999 ; i++)
			;
		putc(c, stdout);//c를 stdout한다.
	}
}


main()
{
	pid_t pid;

	if ((pid = fork()) < 0)  {//fork하고 음수면 에러
		perror("fork");
		exit(1);
	}
	else if (pid == 0)  {//child면
		CharAtaTime("output from child\n");
	} 
	else  {//parent면
		CharAtaTime("output from parent\n");
	}
}
