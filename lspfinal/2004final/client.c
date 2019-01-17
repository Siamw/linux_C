#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "tcp.h"


main(int argc, char *argv[])
{
        int                                     sockfd, n;
        struct sockaddr_in      servAddr;
        MsgType                         msg;
	struct hostent		*hp;
        int on;

        /* socket */
        if ( ( sockfd = socket(PF_INET, SOCK_STREAM, 0) ) < 0   )  {
                perror("socket");
                exit(1);
        }

	on = 1;
        setsockopt( sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on ) );

        /* sockaddr_in 구조체 초기화 */
        bzero((char *)&servAddr, sizeof(servAddr));

        /*  주소 체계 정보 대입 */
        servAddr.sin_family = PF_INET;

        // servAddr.sin_addr.s_addr = htonl(inet_addr(SERV_HOST_ADDR));


	if (isdigit(argv[1][0]))  {
              servAddr.sin_addr.s_addr = htonl(inet_addr(argv[1]));
        }
        else  {
                   /* 문자열을 가지고 호스트의 정보를 가져온다. */
                   if ( ( hp = gethostbyname(argv[1]) ) == NULL)  {
                             fprintf(stderr, "Unknown host: %s\n", argv[1]);
                             exit(1);
                    }

                    /* 호스트 정보를 대입 */
                    memcpy(&servAddr.sin_addr, hp->h_addr, hp->h_length);
        }


        /* 16 비트 포트 정보를 네트워크 바이트 순서로 변경하여 저장 */
        servAddr.sin_port = htons(SERV_TCP_PORT);

        /* tcps.c 에서는 bind 함수를 통하여 클라이언트 소켓에 주소를 할당하는
           부분이 없는데 이러한 경우 커널이 알아서 호스트에 할당되어 있는 IP 주소를
           찾고, 남아도는 Port 를 잡아서 bind 해준다. */


        /* connect */
        /* 서버에 연결 요청을 한다. */
        if ( ( connect( sockfd, (struct sockaddr*)&servAddr, sizeof(servAddr) ) ) < 0  )  {
                perror("connect");
                exit(1);
	}


	msg.type = MSG_REQUEST;
        // sprintf(msg.data, "This is a request from %d.", getpid());
	// sprintf( msg.data, argv[2] );
	strcpy( msg.data, argv[2]);

        /* write */
        /* 서버에 데이터 전송  */
        if ( ( write( sockfd, (char*)&msg, sizeof(msg)  ) ) < 0    )  {
                perror("write");
                exit(1);
        }

        /* read */
	/*
        if ( ( read( sockfd, (char*)&msg, sizeof(msg)  ) ) < 0 )  {
                perror("read");
                exit(1);
        }
        printf("Received reply: %s\n", msg.data);
	*/

        close(sockfd);
}















