#include <stdio.h>
#include <signal.h>

void SigIntHandler( int signo ) 
{
	if( signal( SIGINT, SigIntHandler ) < 0 ) { 
		perror("signal");
		exit(1);
	} 
}




main()
{
	if( signal( SIGINT, (void*)SigIntHandler )  < 0 ) 
	{ 
		perror("signal");
		exit(1);
	}

	while(1);
}
