#include <stdio.h>
#include <signal.h>

void SigUsrHandler(int signo)//handler
{
	if (signo == SIGUSR1)  {//signo가 SIGUSR1일 때
		printf("Received a SIGUSR1 signal\n");
	}
	else if (signo == SIGUSR2)  {//2일때
		printf("Received a SIGUSR2 signal\n");
	}
	else  {//둘다아니면
		printf("Received unknown signal\n");
		printf("Terminate this process\n");
		exit(0);
	}
}

main()
{
/* SIGUSR1 signal handler: SigUsrHandler */
	if (signal(SIGUSR1,SigUsrHandler)==SIG_ERR)  {//USR1일때
		perror("signal");
		exit(1);
	}

	if (signal(SIGUSR2, SigUsrHandler) == SIG_ERR)  {//USR2일때
		perror("signal");
		exit(1);
	}

	for ( ; ; )
	pause();
}
