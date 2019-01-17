#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFSIZE		30

int main( int argc, char **argv ) 
{
	int fd[2];
	char buffer[BUFSIZE];
	pid_t pid;
	int   state;

	if ( ( state = pipe( fd ) ) < 0 ) { 
		perror("pipe");
		exit(1);
	}

	if( ( pid = fork() ) < 0 ) { 
		perror("fork");
		exit(1);
	}	
	else if( pid ==  0 ) { 
		write( fd[1], "Good\n", 6 );
	}
	else  { 
		read( fd[0] , buffer, BUFSIZE );
		puts(buffer );
	}

	return 0;
}
	
	

	

	
		

