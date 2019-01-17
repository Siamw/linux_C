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
		printf("\nTCP Server exit.....\n");

		exit(0);
}


main(int argc, char *argv[])
{
		int newSockfd, cliAddrLen, n;
		struct sockaddr_in cliAddr, servAddr;
		MsgType msg;

		signal(SIGINT, CloseServer);

		if ((Sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)  {
				perror("socket");
				exit(1);
		}
//소켓주소 설정
		bzero((char *)&servAddr, sizeof(servAddr));//0 초기화
		servAddr.sin_family = PF_INET;//internet
		servAddr.sin_addr.s_addr = htonl(INADDR_ANY);//IPv4 address
		servAddr.sin_port = htons(SERV_TCP_PORT);//tcp port number 
//묶어준다
		if (bind(Sockfd, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)  {
				perror("bind");
				exit(1);
		}
//동시에 5개
		listen(Sockfd, 5);

		printf("TCP Server started.....\n");

		cliAddrLen = sizeof(cliAddr);
		while (1)  {
			//connection맺어지기를 기다린다. clinAddr는 아직 확정되지않았ㄴ다. 누구랑 연결
			//되는지 모르기 때문. 연락이 되면 상대방의 정보가 cliAddr에 저장된다. 
			//이 상황에서 clinet실행!
			newSockfd = accept(Sockfd, (struct sockaddr *) &cliAddr, &cliAddrLen);
					// connection이 이루어지면, 새로운 소켓이 생긴다 newSockfd
					// 이 새로생긴 fd를 가지고 정보를 주고받는다. 그냥 Sockfd는 
					// tcp connection 주고받기위한 소켓.
				if (newSockfd < 0)  {
						perror("accept");
						exit(1);
				}
//////////////전체를 새로운 프로세스로 넘기고 (fork) parent는 newsocketfd close
int pid;
		if((pid = fork())<0){
		perror("fork error");
		exit(0);
		}

		if(pid==0){
				if ((n = read(newSockfd, (char *)&msg, sizeof(msg))) < 0)  {
						perror("read");
						exit(1);
				}
				printf("Received request: %s.....", msg.data);

				msg.type = MSG_REPLY;
				sprintf(msg.data, "This is a reply from %d.", getpid());
				if (write(newSockfd, (char *)&msg, sizeof(msg)) < 0)  {
						perror("write");
						exit(1);
				}
				printf("Replied.\n");
			}
			
			else{
				usleep(10000);
				close(newSockfd);
			}
		
		}
}
