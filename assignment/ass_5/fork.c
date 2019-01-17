#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int Var = 6;
char Buf[] = "a write to stdout\n";

main()
{
	int var;
	pid_t pid;

	var = 88;
	write(STDOUT_FILENO, Buf, sizeof(Buf)-1);//Buf내용을 STDOUT_FILENO에 넣는다. 즉 출력한다.
	printf("Before fork\n");

	if ((pid = fork()) < 0)  {//fork를 하고, 음수가 리턴되면 에러
	perror("fork");
	exit(1);
	}
	else if (pid == 0)  {// child면 var, Var ++
	/* child */
	Var++;
	var++;
	}
	else  {//parent면 ++ X
	/* parent */
	sleep(2);
	}

	printf("pid = %d, Var = %d, var = %d\n", getpid(), Var, var);
}
