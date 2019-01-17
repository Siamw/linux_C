#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFSIZE 	30

int main( int argc, char** argv )
{
	int fd1[2], fd2[2];
	char buffer[BUFSIZE];
	pid_t pid;

	if ( pipe(fd1) < 0  || pipe(fd2)  < 0 ) { 
		perror("pipe");	
		exit(1);
	}

	if ( ( pid = fork() ) < 0 ) { 
		perror("fork");
		exit(1);
	}
	else if( pid == 0 ) { 

		close( fd1[0] );
	        close( fd2[1] );

		write( fd1[1], "Good!", 6 );
		read(  fd2[0], buffer, BUFSIZE );
		printf("자식 프로세스 출력 : %s \n\n", buffer );
	}
	else { 
		close( fd1[1] );
		close( fd2[0] );

		read ( fd1[0] , buffer, BUFSIZE );
		printf("부모 프로세스 출력 : %s \n", buffer );
		write( fd2[1], "Really Good", 12 );
	}

	return 0;

}

	

	
	
	

	
