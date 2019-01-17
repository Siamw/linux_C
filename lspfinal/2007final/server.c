#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include "tcp.h"

int     Sockfd;

void
CloseServer()
{
        close(Sockfd);
        printf("\nTCP Server exit.....\n");

        exit(0);
}

main(int argc, char *argv[])
{
        int                     newSockfd, cliAddrLen, n;
        struct sockaddr_in      cliAddr, servAddr;
        MsgType                         msg;
        pid_t                           pid;
        FILE                    *dst1;
        struct   timeval        mytime;
        long                    time;
        char                    buf[128];
        int                     len;
	int			on;
	

        /*  Ctrl +  C 를 눌렀을 시 핸들러 처리 함수 등록
            소켓을 닫아주고 프로그램을 종료한다. */
        signal(SIGINT, CloseServer);

         /*  TCP 소켓 생성. PF_INET 은 IPV4 인터넷 프로토콜로 통신할 때
            설정하고 SOCK_STREAM 은 연결 지향형 소켓을 만들 때 설정. */
        if ( ( Sockfd = socket(PF_INET, SOCK_STREAM, 0) ) < 0 )  {
                perror("socket");
                exit(1);
        }


	on = 1;
        setsockopt( Sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on) );


        /* oockaddr_in 구조체 초기화 */
        bzero((char *)&servAddr, sizeof(servAddr));
        /* 주소 체계 정보 대입 */
	  servAddr.sin_family = PF_INET;
        /* 32 비트 ip 주소 정보를 호스트 바이트에서
           네트워크 바이트  순서로 변경하여 저장 */
        servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
        /* 16 비트 포트 정보를 네트워크 바이트 순서로 변경하여 저장 */
        servAddr.sin_port = htons(SERV_TCP_PORT);

        /* 소켓에 주소 정보를 할당한다. */
        if ( bind(Sockfd, (struct sockaddr *) &servAddr, sizeof(servAddr) ) < 0)  {
                perror("bind");
                exit(1);
        }

        /* 연결 요청 대기 상태. 5개의 요청을 처리할 수 있음을 의미  */
        listen(Sockfd, 5);

        printf("TCP Server started.....\n");

        cliAddrLen = sizeof(cliAddr);


        while (1)  {

                newSockfd = accept( Sockfd, (struct sockaddr *)&cliAddr, &cliAddrLen );

                if( ( pid = fork() ) < 0 )  {
                        perror("fork");
                        exit(1);
                }
                else if ( pid == 0 ) {
                        /*  데이터 송수신은 자식 프로세스가 전담한다.
                            자식 프로세스는 Sockfd  소켓이 필요없으므로 복사된
                            서버 소켓을 닫아 준다. */
                        close( Sockfd );

                        if ( newSockfd < 0 )  {
                                perror("accept");
                                exit(1);
                        }

			
                        /*  데이터를 읽어온다. */
                        if ((n = read( newSockfd, (char *)&msg, sizeof(msg))) < 0)  {
                                perror("read");
                                exit(1);
                        }

			printf("%s\n", msg.fileName );
			printf("%s\n", msg.data );
                        usleep(10000);

                        close( newSockfd );
                        exit(0);
                }
                else {
                        /* 자식 프로세스가 클라이언트와 데이터를 주고 받게 되므로
                           부모 프로세스는 newSockfd 소켓이 필요없어 닫아준다. */
                        close( newSockfd );
                }

        }
}




