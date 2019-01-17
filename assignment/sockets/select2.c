#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>
#include "select.h"
#include <pthread.h>
#include <stdlib.h>

int TcpSockfd;
int UdpSockfd;
int UcoSockfd;
int UclSockfd;

		void
CloseServer()
{
		close(TcpSockfd);
		close(UdpSockfd);
		close(UcoSockfd);
		close(UclSockfd);
		if (remove(UNIX_STR_PATH) < 0)  {
				perror("remove");
		}
		if (remove(UNIX_DG_PATH) < 0)  {
				perror("remove");
		}

		printf("\nServer daemon exit.....\n");

		exit(0);
}

		void
MakeTcpSocket()
{
		struct sockaddr_in servAddr;

		if ((TcpSockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)  {
				perror("socket");
				exit(1);
		}

		bzero((char *)&servAddr, sizeof(servAddr));
		servAddr.sin_family = PF_INET;
		servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
		servAddr.sin_port = htons(SERV_TCP_PORT);

		if (bind(TcpSockfd, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)  {
				perror("bind");
				exit(1);
		}

		listen(TcpSockfd, 5);
}

		void
MakeUdpSocket()
{
		struct sockaddr_in servAddr;

		if ((UdpSockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0)  {
				perror("socket");
				exit(1);
		}

		bzero((char *)&servAddr, sizeof(servAddr));
		servAddr.sin_family = PF_INET;
		servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
		servAddr.sin_port = htons(SERV_UDP_PORT);

		if (bind(UdpSockfd, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)  {
				perror("bind");
				exit(1);
		}

}

		void
MakeUcoSocket()
{
		struct sockaddr_un servAddr;
		int servAddrLen;

		if ((UcoSockfd = socket(PF_UNIX, SOCK_STREAM, 0)) < 0)  {
				perror("socket");
				exit(1);
		}

		bzero((char *)&servAddr, sizeof(servAddr));
		servAddr.sun_family = PF_UNIX;
		strcpy(servAddr.sun_path, UNIX_STR_PATH);
		servAddrLen = strlen(servAddr.sun_path) + sizeof(servAddr.sun_family);

		if (bind(UcoSockfd, (struct sockaddr *) &servAddr, servAddrLen) < 0)  {
				perror("bind");
				exit(1);
		}

		listen(UcoSockfd, 5);

}

		void
MakeUclSocket()
{
		struct sockaddr_un servAddr;
		int servAddrLen;

		if ((UclSockfd = socket(PF_UNIX, SOCK_DGRAM, 0)) < 0)  {
				perror("socket");
				exit(1);
		}

		bzero((char *)&servAddr, sizeof(servAddr));
		servAddr.sun_family = PF_UNIX;
		strcpy(servAddr.sun_path, UNIX_DG_PATH);
		servAddrLen = strlen(servAddr.sun_path) + sizeof(servAddr.sun_family);

		if (bind(UclSockfd, (struct sockaddr *) &servAddr, servAddrLen) < 0)  {
				perror("bind");
				exit(1);
		}

}

		void
ProcessTcpRequest()
{
		int newSockfd, cliAddrLen, n;
		struct sockaddr_in cliAddr;
		MsgType msg;

		cliAddrLen = sizeof(cliAddr);
		newSockfd = accept(TcpSockfd, (struct sockaddr *) &cliAddr, &cliAddrLen);
		if (newSockfd < 0)  {
				perror("accept");
				exit(1);
		}

		if ((n = read(newSockfd, (char *)&msg, sizeof(msg))) < 0)  {
				perror("read");
				exit(1);
		}
		printf("Received TCP request: %s.....", msg.data);

		msg.type = MSG_REPLY;
		sprintf(msg.data, "This is a reply from %d.", getpid());
		if (write(newSockfd, (char *)&msg, sizeof(msg)) < 0)  {
				perror("write");
				exit(1);
		}
		printf("Replied.\n");

		close(newSockfd);
}

		void
ProcessUdpRequest()
{
		int cliAddrLen, n;
		struct sockaddr_in cliAddr;
		MsgType msg;

		cliAddrLen = sizeof(cliAddr);
		if ((n = recvfrom(UdpSockfd, (char *)&msg, sizeof(msg), 
										0, (struct sockaddr *)&cliAddr, &cliAddrLen)) < 0)  {
				perror("recvfrom");
				exit(1);
		}
		printf("Received UDP request: %s.....", msg.data);

		msg.type = MSG_REPLY;
		sprintf(msg.data, "This is a reply from %d.", getpid());
		if (sendto(UdpSockfd, (char *)&msg, sizeof(msg),
								0, (struct sockaddr *)&cliAddr, cliAddrLen) < 0)  {
				perror("sendto");
				exit(1);
		}
		printf("Replied.\n");
}

		void
ProcessUcoRequest()
{
		int newSockfd, cliAddrLen, n;
		struct sockaddr_un cliAddr;
		MsgType msg;

		cliAddrLen = sizeof(cliAddr);
		newSockfd = accept(UcoSockfd, (struct sockaddr *) &cliAddr, &cliAddrLen);
		if (newSockfd < 0)  {
				perror("accept");
				exit(1);
		}

		if ((n = read(newSockfd, (char *)&msg, sizeof(msg))) < 0)  {
				perror("read");
				exit(1);
		}
		printf("Received UNIX-domain CO request: %s.....", msg.data);

		msg.type = MSG_REPLY;
		sprintf(msg.data, "This is a reply from %d.", getpid());
		if (write(newSockfd, (char *)&msg, sizeof(msg)) < 0)  {
				perror("write");
				exit(1);
		}
		printf("Replied.\n");

		close(newSockfd);
}

		void
ProcessUclRequest()
{
		int cliAddrLen, n;
		struct sockaddr_un cliAddr;
		MsgType msg;

		cliAddrLen = sizeof(cliAddr);
		if ((n = recvfrom(UclSockfd, (char *)&msg, sizeof(msg), 
										0, (struct sockaddr *)&cliAddr, &cliAddrLen)) < 0)  {
				perror("recvfrom");
				exit(1);
		}
		printf("Received UNIX-domain CL request: %s.....", msg.data);

		msg.type = MSG_REPLY;
		sprintf(msg.data, "This is a reply from %d.", getpid());
		if (sendto(UclSockfd, (char *)&msg, sizeof(msg),
								0, (struct sockaddr *)&cliAddr, cliAddrLen) < 0)  {
				perror("sendto");
				exit(1);
		}
		printf("Replied.\n");
}

main(int argc, char *argv[])
{
		fd_set fdvar;
		int count;

		signal(SIGINT, CloseServer);

//소켓 만드는 코드
		MakeTcpSocket();
		MakeUdpSocket();
		MakeUcoSocket();
		MakeUclSocket();

		printf("Server daemon started.....\n");

		while (1)  {
				FD_ZERO(&fdvar);
				FD_SET(TcpSockfd, &fdvar);
				FD_SET(UdpSockfd, &fdvar);
				FD_SET(UcoSockfd, &fdvar);
				FD_SET(UclSockfd, &fdvar);
				if ((count = select(10, &fdvar, (fd_set *)NULL, (fd_set *)NULL,(struct timeval *)NULL))<0/* select */)  {
			//10이라는 넉넉한 소켓 디스크립터.0~ 10 까지만 검사하면 된다.
			//fdvar라고하는 구조체에 설정한 소켓만 검사하면 된다.. 위 fd-set에서 넣어주었다.
			//쟤네중 패킷이 올 때 까지 영원히 ( timeval = NULL ) 기다린다.
			perror("select");
						exit(1);
						//count = 도착한 패킷의 수. 보통 1이지만, 동시에오면 ㅇ더 클 수 있음. 
				}
	
	
	pthread_t p_thread[4];
	int thr_id = 0 ;
	int status;
	char p1[] = "1";
	char p2[] = "2";
	char p3[] = "3";
	char p4[] = "4";

	while (count--)  {
	
		////////////processSSSSS들을 실행할 pthread를 만들어주면된다.

	thr_id = pthread_create(&p_thread[0], NULL,&ProcessTcpRequest(),(void *)p1);
	thr_id = pthread_create(&p_thread[1], NULL, &ProcessUdpRequest(),(void *)p2);
	thr_id = pthread_create(&p_thread[2], NULL, &ProcessUcoRequest(),(void *)p3);
	thr_id = pthread_create(&p_thread[3], NULL, &ProcessUclRequest(),(void *)p4);


			
	pthred_join(p_thread[0], (void **)&status);
	pthread_join(p_thread[1], (void **)&status);
	pthread_join(p_thread[2], (void **)&status);
    pthread_join(p_thread[3], (void **)&status);


//count>1이면, fd_isset으로 어디서 데이터가 온것인지 알아낸다. 
/*				if (FD_ISSET(TcpSockfd, &fdvar))  {
								ProcessTcpRequest();
						}
						else if (FD_ISSET(UdpSockfd, &fdvar))  {
								ProcessUdpRequest();
						}
						else if (FD_ISSET(UcoSockfd, &fdvar))  {
								ProcessUcoRequest();
						}
						else if (FD_ISSET(UclSockfd, &fdvar))  {
								ProcessUclRequest();
						}*/


				}
		}
}
