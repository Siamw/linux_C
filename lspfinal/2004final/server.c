#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include "tcp.h"

int Sockfd;

void
CloseServer()
{
        close(Sockfd);
        printf("\nTerminated.....\n");

        exit(0);
}

main(int argc, char *argv[])
{
        int                     newSockfd, cliAddrLen, n;
        struct sockaddr_in      cliAddr, servAddr;
        MsgType                         msg;
	int on;


        signal(SIGINT, CloseServer);

        if ((Sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)  {
                perror("socket");
                exit(1);
        }

	on = 1;
	setsockopt( Sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on ) );

        bzero((char *)&servAddr, sizeof(servAddr));
        servAddr.sin_family = PF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
        servAddr.sin_port = htons(SERV_TCP_PORT);

        /* 소켓에 주소 정보를 할당한다. */
        if (bind(Sockfd, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)  {
                perror("bind");
                exit(1);
        }

        listen(Sockfd, 5);

        cliAddrLen = sizeof(cliAddr);

        while (1)  {
		newSockfd = accept(Sockfd, (struct sockaddr *) &cliAddr, &cliAddrLen);

                if (newSockfd < 0)  {
                        perror("accept");
                        exit(1);
                }

                /*  데이터를 읽어온다. */
                if ((n = read(newSockfd, (char *)&msg, sizeof(msg))) < 0)  {
                        perror("read");
                        exit(1);
                }

   		printf("Received message: %s.....\n", msg.data);

		/*
                msg.type = MSG_REPLY;
                sprintf(msg.data, "This is a reply from %d.", getpid());
		*/

                /* 데이터를 전송한다. */
		/*
                if (write(newSockfd, (char *)&msg, sizeof(msg)) < 0)  {
                        perror("write");
                        exit(1);
                }
                printf("Replied.\n");
	        */		

   		usleep(10000);
                close(newSockfd);
		
        }
}

