#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <time.h>
#include <netdb.h>
#include <sys/time.h>

#define BUFSIZE 1024


void error_handling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
}


int main(int argc, char** argv)
{
	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	int clnt_addr_size;

	int serv_sock;
	int clnt_sock;
	int str_len;
	char message[BUFSIZE];
	int cnt = 0;

	struct timeval tv;

	if( argc!=2 ){
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	// socket()
	serv_sock = socket(PF_INET, SOCK_DGRAM, 0);  // UDP
	if( serv_sock==-1 )
		error_handling("socket() error!");

	// serv_addr
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = atoi( argv[1] );

	// bind()
	if( bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1 )
		error_handling("bind() error!");

	clnt_addr_size = sizeof(clnt_addr);

	for(cnt=0; ; cnt++)
	{
		recvfrom(serv_sock, message, BUFSIZE, 0, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
//		usleep(45232);
		sendto(serv_sock, message, sizeof(tv), 0, (struct sockaddr*)&clnt_addr, sizeof(clnt_addr));

		memcpy(&tv, message, sizeof(tv));
		printf("%s: %d sec. \n", inet_ntoa(clnt_addr.sin_addr), tv.tv_sec);
	}

	close(serv_sock);
	return 0;
}

