#include <stdio.h>
#include <signal.h>

#define MAX_BUF 300

static int count;
static FILE* file;

void SigAlarmHandler(int signo)//alarm handler
{
	if (signal(SIGALRM,SigAlarmHandler)==SIG_ERR)  {//에러나면
		perror("signal");
		exit(1);
	
	}

	fprintf(file,"%d\n", ++count);//file에 print함

	return;
}

void sigint_handler(int signo){
	fclose(file);//file close
	exit(0);
}

int
SetPeriodicAlarm(int nsecs)
{
if (signal(SIGALRM,SigAlarmHandler)==SIG_ERR)  {//에러나면
	return -1;
}

ualarm(nsecs,nsecs);//0.5초마다 출력하기 위해 ualarm사용

return 0;
}

main()
{
signal(SIGINT, sigint_handler);//종료할때 sigint_handler
file = fopen("alarm.txt", "wb");//file에 alarm.txt write only로 bite file open
SetPeriodicAlarm(500000);//반복적인 알람 1초 

for ( ; ; )
pause();
}
