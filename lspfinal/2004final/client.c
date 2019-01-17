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

        /* sockaddr_in ����ü �ʱ�ȭ */
        bzero((char *)&servAddr, sizeof(servAddr));

        /*  �ּ� ü�� ���� ���� */
        servAddr.sin_family = PF_INET;

        // servAddr.sin_addr.s_addr = htonl(inet_addr(SERV_HOST_ADDR));


	if (isdigit(argv[1][0]))  {
              servAddr.sin_addr.s_addr = htonl(inet_addr(argv[1]));
        }
        else  {
                   /* ���ڿ��� ������ ȣ��Ʈ�� ������ �����´�. */
                   if ( ( hp = gethostbyname(argv[1]) ) == NULL)  {
                             fprintf(stderr, "Unknown host: %s\n", argv[1]);
                             exit(1);
                    }

                    /* ȣ��Ʈ ������ ���� */
                    memcpy(&servAddr.sin_addr, hp->h_addr, hp->h_length);
        }


        /* 16 ��Ʈ ��Ʈ ������ ��Ʈ��ũ ����Ʈ ������ �����Ͽ� ���� */
        servAddr.sin_port = htons(SERV_TCP_PORT);

        /* tcps.c ������ bind �Լ��� ���Ͽ� Ŭ���̾�Ʈ ���Ͽ� �ּҸ� �Ҵ��ϴ�
           �κ��� ���µ� �̷��� ��� Ŀ���� �˾Ƽ� ȣ��Ʈ�� �Ҵ�Ǿ� �ִ� IP �ּҸ�
           ã��, ���Ƶ��� Port �� ��Ƽ� bind ���ش�. */


        /* connect */
        /* ������ ���� ��û�� �Ѵ�. */
        if ( ( connect( sockfd, (struct sockaddr*)&servAddr, sizeof(servAddr) ) ) < 0  )  {
                perror("connect");
                exit(1);
	}


	msg.type = MSG_REQUEST;
        // sprintf(msg.data, "This is a request from %d.", getpid());
	// sprintf( msg.data, argv[2] );
	strcpy( msg.data, argv[2]);

        /* write */
        /* ������ ������ ����  */
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















