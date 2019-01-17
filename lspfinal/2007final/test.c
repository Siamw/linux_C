#include <stdio.h>
#include <unistd.h>
#include <signal.h>


void
SigAlarmHandler(int signo)
{
	pid_t pid;
        int status;

        if( ( pid = fork() ) < 0 )  {
                perror( "fork" );
                exit(1);
        }
        else if ( pid == 0 )  {   /* 자식 프로세스 처리 */
                execlp( "banner", "banner" , "lunch", NULL );
        }
        else
        {
                wait(&status);
        }
	
	exit(0);

}


main( int argc, char* argv[] )
{
	signal( SIGALRM, SigAlarmHandler );
	int n;

	n = atoi( argv[1] );

	alarm(n);

	while(1);
	
}

