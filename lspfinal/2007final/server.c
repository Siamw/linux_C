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
	

        /*  Ctrl +  C �� ������ �� �ڵ鷯 ó�� �Լ� ���
            ������ �ݾ��ְ� ���α׷��� �����Ѵ�. */
        signal(SIGINT, CloseServer);

         /*  TCP ���� ����. PF_INET �� IPV4 ���ͳ� �������ݷ� ����� ��
            �����ϰ� SOCK_STREAM �� ���� ������ ������ ���� �� ����. */
        if ( ( Sockfd = socket(PF_INET, SOCK_STREAM, 0) ) < 0 )  {
                perror("socket");
                exit(1);
        }


	on = 1;
        setsockopt( Sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on) );


        /* oockaddr_in ����ü �ʱ�ȭ */
        bzero((char *)&servAddr, sizeof(servAddr));
        /* �ּ� ü�� ���� ���� */
	  servAddr.sin_family = PF_INET;
        /* 32 ��Ʈ ip �ּ� ������ ȣ��Ʈ ����Ʈ����
           ��Ʈ��ũ ����Ʈ  ������ �����Ͽ� ���� */
        servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
        /* 16 ��Ʈ ��Ʈ ������ ��Ʈ��ũ ����Ʈ ������ �����Ͽ� ���� */
        servAddr.sin_port = htons(SERV_TCP_PORT);

        /* ���Ͽ� �ּ� ������ �Ҵ��Ѵ�. */
        if ( bind(Sockfd, (struct sockaddr *) &servAddr, sizeof(servAddr) ) < 0)  {
                perror("bind");
                exit(1);
        }

        /* ���� ��û ��� ����. 5���� ��û�� ó���� �� ������ �ǹ�  */
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
                        /*  ������ �ۼ����� �ڽ� ���μ����� �����Ѵ�.
                            �ڽ� ���μ����� Sockfd  ������ �ʿ�����Ƿ� �����
                            ���� ������ �ݾ� �ش�. */
                        close( Sockfd );

                        if ( newSockfd < 0 )  {
                                perror("accept");
                                exit(1);
                        }

			
                        /*  �����͸� �о�´�. */
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
                        /* �ڽ� ���μ����� Ŭ���̾�Ʈ�� �����͸� �ְ� �ް� �ǹǷ�
                           �θ� ���μ����� newSockfd ������ �ʿ���� �ݾ��ش�. */
                        close( newSockfd );
                }

        }
}




