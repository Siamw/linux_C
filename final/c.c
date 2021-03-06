#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "udp.h"


main(int argc, char *argv[])
{
		int  sockfd, n, peerAddrLen;
		struct sockaddr_in servAddr, peerAddr;
		MsgType msg;
		struct hostent *hp;

		if (argc != 3)  {
				fprintf(stderr, "Usage: %s IPaddress\n", argv[0]);
				exit(1);
		}

		if ((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0/* socket */)  {
			//ipv4, tcp/ip
				perror("socket");
				exit(1);
		}

		bzero((char *)&servAddr, sizeof(servAddr));
		servAddr.sin_family = PF_INET;
		servAddr.sin_port = htons(SERV_UDP_PORT);

		if (isdigit(argv[1][0]))  {//첫번째 캐릭터가 숫자면,
				servAddr.sin_addr.s_addr = inet_addr(argv[1]);
		}
		else  {//아니면 이름이니까 !
				if ((hp = gethostbyname(argv[1])) == NULL)  {
						fprintf(stderr, "Unknown host: %s\n", argv[1]);
						exit(1);
				}
				//addr, 4를 ip address에 넣는 것 수행
				memcpy(&servAddr.sin_addr, hp->h_addr, hp->h_length);
		}

		msg.type = MSG_REQUEST;
		sprintf(msg.data, "This is a request from %d.", getpid());
		sprintf(msg.id,"%d",argv[2]);
		if (sendto(sockfd, (char *)&msg, sizeof(msg),0,(struct sockaddr *)&servAddr, sizeof(servAddr))<0/* write */)  {//sockfd에 msg씀
				perror("write");
				exit(1);
		}
		printf("Sent a request.....");

		peerAddrLen = sizeof(peerAddr);
		if ((n = recvfrom(sockfd, (char *)&msg, sizeof(msg),0,(struct sockaddr *)&peerAddr, &peerAddrLen)) < 0/* read */)  {
				perror("read");
				exit(1);
		}
		printf("Received reply: %s\n", msg.data);

		close(sockfd);
}
