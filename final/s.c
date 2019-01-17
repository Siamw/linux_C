#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include "udp.h"


int Sockfd;

		void
CloseServer()
{
		close(Sockfd);
		printf("\nUDP Server exit.....\n");

		exit(0);
}


main(int argc, char *argv[])
{
		int cliAddrLen, n;
		struct sockaddr_in cliAddr, servAddr;
		MsgType msg;

		signal(SIGINT, CloseServer);

		if ((Sockfd = socket(PF_INET, SOCK_DGRAM,0))<0/* socket */)  {
		//소켓을 생성한다. IPv4 사용, udp/ip
				perror("socket");
				exit(1);
		}

		bzero((char *)&servAddr, sizeof(servAddr));//0으로 채운다.
		//struct sockaddr_in
		servAddr.sin_family = PF_INET;
		servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
		servAddr.sin_port = htons(SERV_UDP_PORT);

		if (bind(Sockfd, (struct sockaddr *) &servAddr, sizeof(servAddr))<0/* bind */)  {
			//socket discriptor, servAddr
			//소켓에 ip주소와 포트번호 지정해준다. 
				perror("bind");
				exit(1);
		}

		printf("UDP Server started.....\n");

		cliAddrLen = sizeof(cliAddr);
		while (1)  {
				if ((n = recvfrom(Sockfd, (char*)&msg, sizeof(msg), 
						0, (struct sockaddr *)&cliAddr, &cliAddrLen))<0/* recvfrom */)  {
				// udp/ip 통신에서 소켓으로부터 데이터를 수신한다.
				//소켓 디스크립터, 버퍼포인터, 버퍼크기
				//flags(option), 전송한 곳의 주소 정보, 주조 정보의 크기
						perror("recvfrom");
						exit(1);
				}
				printf("lsp%d login (UID = %d)", msg.id, msg.id);

				msg.type = MSG_REPLY;
				sprintf(msg.data, "This is a reply from %d.", getpid());
				if (sendto(Sockfd, (char *)&msg, sizeof(msg),
					0, (struct sockaddr *)&cliAddr, cliAddrLen) < 0/* sendto */)  {//받은거 그대로 보냄
					//udp/ip 통신에서 소켓으로 데이터를 전송한다.
					//소켓 디스크립터, 전송할 데이터, 길이
					// flags, 주소정보, 크기
						perror("sendto");
						exit(1);
				}
				printf("Replied.\n");
		}
}
