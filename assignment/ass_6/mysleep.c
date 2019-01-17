#include <stdio.h>
#include <signal.h>

void SigAlarmHandler(int signo)
{
/* nothing to do, just return to wake up the pause */
	printf("healfjsliefjasldkfjaslkdjl`");
	return;
}

unsigned int mysleep(unsigned int nsecs)
{
/* SIGALRM signal handler: SigAlarmHandler */
	if (signal(SIGALRM,SigAlarmHandler)==SIG_ERR)  {//handler
		return nsecs;
	}

	alarm(nsecs);/* alarm *///nsecs초 후 전달

	pause();

	return alarm(0);
}

main()
{
printf("Wait for 5 seconds...\n");

mysleep(5);
}
