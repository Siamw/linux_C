#include <stdio.h>
#include <signal.h>

#define FILENAME "./.ctrlc"

int count = 0;

/*
void SigIntHandler( int signo ) 
{
	FILE* file;	
	
	if( ( file =  fopen( FILENAME, "wt") ) == NULL ) { 
		perror("fopen");
		exit(1);
	}

	count++;
	printf("\nDon't press ^C\n");

	fprintf( file, "%d", count );

	fclose( file );

	if( signal( SIGINT, SigIntHandler ) < 0 ) { 
		perror("signal");
		exit(1);
	} 
}
*/

void SigIntHandler( int signo ) 
{
	count++;
	printf("\nDon't press ^C\n");

        if( signal( SIGINT, SigIntHandler ) < 0 ) { 
		perror("signal");
		exit(1);
	}

}

void SigQuitHandler( int signo ) 
{
	FILE* file;	
	
	if( ( file =  fopen( FILENAME, "wt") ) == NULL ) { 
		perror("fopen");
		exit(1);
	}

	fprintf( file, "%d", count );

	fclose( file );

	exit(0);
}

main()
{
	if( signal( SIGINT, (void*)SigIntHandler )  < 0 ) 
	{ 
		perror("signal");
		exit(1);
	}

	if ( signal( SIGQUIT, (void*)SigQuitHandler ) < 0 ) 
        { 
		perror("signal");
		exit(1);
        }

	while(1);

}
