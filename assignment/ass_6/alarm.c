#include <stdio.h>
#include <signal.h>

static unsigned int AlarmSecs;


void SigAlarmHandler(int signo)//alarm handler
{//unix나 다른환경 대비하여 signal 한번 사용 후 없어질수도 있으므로 여기에도 만들어준다.
	if (signal(SIGALRM,SigAlarmHandler)==SIG_ERR/* signal */)  {
		perror("signal");
		exit(1);
	}

/* alarm */
alarm(AlarmSecs);

/* Do something */
printf(".");
fflush(stdout);//출력스트림의 버퍼를 비운다.

return;
}

int
SetPeriodicAlarm(unsigned int nsecs)
{//여기서signal  만들어줌.
	if (signal(SIGALRM,SigAlarmHandler)==SIG_ERR/* signal */)  {
	return -1;
}

AlarmSecs = nsecs;//몇초?handler에서 사용하기 위한 코드

alarm(nsecs);/* alarm */

return 0;
}

main()
{
printf("Doing something every one seconds\n");

SetPeriodicAlarm(1);//반복적인 알람 1초 

for ( ; ; )
pause();
}
