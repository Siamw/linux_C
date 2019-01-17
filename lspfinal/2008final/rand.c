#include <stdio.h>
#include <unistd.h>
#include <signal.h>


int sig_Cnt=0;
int count[3];

void
sigintHandler(int signo)
{
	printf("\n%d\n",count[sig_Cnt]);
	sig_Cnt++;
	
	if(sig_Cnt == 3)
		rand_exit();
}

rand_exit() 
{
	printf("Random number : %d, %d, %d\n ",
				count[0], count[1], count[2]);
	exit(0);
}

main()
{
	int cnt , i = 0;
	
	while(1){	
		for(i=0 ; i<=100; i++)
		{
			count[sig_Cnt] = i;
			signal(SIGINT, (void *)sigintHandler);
		}
	}
}

