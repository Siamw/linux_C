#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "tcp.h"

int     Sockfd;

main(int argc, char *argv[])
{
	int                     newSockfd, cliAddrLen, n;
	struct sockaddr_in      cliAddr, servAddr;
	MsgType					msg;	
	pid_t					pid;
	long					time;
	char					buf[128];
	int						len;
        if ( ( Sockfd = socket(PF_INET, SOCK_STREAM, 0) ) < 0 )  {
                perror("socket");
		exit(1);
        }

        bzero((char *)&servAddr, sizeof(servAddr));
        servAddr.sin_family = PF_INET;
        servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
        servAddr.sin_port = htons(SERV_TCP_PORT);

        if ( bind(Sockfd, (struct sockaddr *) &servAddr, sizeof(servAddr) ) < 0)  {
                perror("bind");
                exit(1);
        }

        listen(Sockfd, 5);

        printf("TCP Server started.....\n");

        cliAddrLen = sizeof(cliAddr);


		newSockfd = accept( Sockfd, (struct sockaddr *)&cliAddr, &cliAddrLen );

		if( ( pid = fork() ) < 0 )  {
			perror("fork");
			exit(1);
		}
        else if ( pid == 0 ) { // child process 
             close( Sockfd );

           		if ((n = read( newSockfd, (char *)&msg, sizeof(msg))) < 0)  {
					error("read");
						exit(1);
                }
				printf("%d", msg.data);
				//close( newSockfd );	
				exit(0);
        }
		 else {
             close( newSockfd );
           }
	
}
