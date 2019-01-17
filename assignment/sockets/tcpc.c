#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "tcp.h"


main(int argc, char *argv[])
{
		int sockfd, n;
		struct sockaddr_in servAddr;
		MsgType msg;

		if ((sockfd = socket(PF_INET,SOCK_STREAM,0))<0/* socket */)  {
				//소켓을 생성하여 반환한다. IPv4사용, TCP/IP프로토콜 이용, 특정 프로토콜 사용을 지정하기 위한 변수이며, 보통 0 사용
				perror("socket");
				exit(1);
		}
		//소켓 주소 설정
		bzero((char *)&servAddr, sizeof(servAddr));//0으로 초기화
		servAddr.sin_family = PF_INET;//
		servAddr.sin_addr.s_addr = inet_addr(SERV_HOST_ADDR);//연결할 서버의 주소
		servAddr.sin_port = htons(SERV_TCP_PORT);

//자기 자신이 쓸 소켓주소 bind할 수도 있고, 안할수도 있다.
//안하면 커널이 비어있는 tcp port아무거나 하나 할당한다. 
//서버는 무조건 bind를 해야하지만, client는 꼭 할필요 없다. 

		if (connect(sockfd, (struct sockaddr *)&servAddr,sizeof(servAddr))<0/* connect */)  {
		//생성한 소켓을 통해 서버로 접속을 요청한다.
		// 소켓 디스크립터, 연결 할 서버 주소 정보에 대한 포인터, 앞 포인터가 가르키는 구조체의 크기
				perror("connect");
				exit(1);
		}

		msg.type = MSG_REQUEST;
		sprintf(msg.data, "This is a request from %d.", getpid());
		if (write(sockfd, (char*)&msg, sizeof(msg))<0/* write */)  {// sockfd에 &msg 하나 씀 
				perror("write");
				exit(1);
		}
		printf("Sent a request.....");

		if ((n = read(sockfd,(char*)&msg, sizeof(msg)))<0/* read */)  {// sockfd &msg하나 읽
				perror("read");
				exit(1);
		}
		printf("Received reply: %s\n", msg.data);

		close(sockfd);
}
