#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFSIZE 	30

int main( int argc, char** argv )
{
	int fd[2];
	char buffer[BUFSIZE];
	pid_t pid;

	if ( ( pipe(fd) )  < 0 ) { 
		perror("pipe");	
		exit(1);
	}

	if ( ( pid = fork() ) < 0 ) { 
		perror("fork");
		exit(1);
	}
	else if( pid == 0 ) { 
		write( fd[1], "Good!", 6 );
//		sleep(2);
		read( fd[0], buffer, BUFSIZE );
		printf("자식 프로세스 출력 : %s \n\n", buffer );
	}
	else { 
		read ( fd[0] , buffer, BUFSIZE );
		printf("부모 프로세스 출력 : %s \n", buffer );
		write( fd[1], "Really Good", 12 );
		sleep(3);
	}

	return 0;

}

	

	
	
	

	
