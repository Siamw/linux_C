#include <stdio.h>
#include <signal.h>

void SigIntHandler(int signo)
{
printf("Received a SIGINT signal\n");
printf("Terminate this process\n");

exit(0);
}

main()
{
/* SIGINT signal handler: SigIntHandler */
/* signal */
signal(SIGINT, SigIntHandler);//대화식 attention 발생시SigIntHandler 함수 실행
printf("Press ^C to quit\n");

for ( ; ; )
pause();
}
