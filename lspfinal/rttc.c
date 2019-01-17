#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netdb.h>

#define BUFSIZE 1024

void getAddrFromHost(char* buf, char* hostname)
{
	struct hostent* hp;
	struct in_addr in;

	hp = gethostbyname( hostname );
	if( hp==NULL ){
		printf("gethostbyname fail\n");
		exit(0);
	}
	
	memcpy(&in.s_addr, hp->h_addr, sizeof(in.s_addr));
	inet_ntop(AF_INET, &in, buf, BUFSIZE);
}

void error_handling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
}

int main(int argc, char** argv)
{
	int i;
	float diff;

	struct hostent* hp;
	struct sockaddr_in serv_addr;
	struct sockaddr_in from_addr;
	int sock;
	int addr_size;

	char message[BUFSIZE];
	char buf[BUFSIZE];

	struct timeval tv1, tv2;

	if( argc!=3 ){
		printf("Usage : %s <addr> <port>\n", argv[0]);
		exit(1);
	}

	// socket()
	sock = socket(PF_INET, SOCK_DGRAM, 0);  // UDP
	if( sock==-1 ){
		error_handling("socket() error!");
		exit(1);
	}

	// serv_addr
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = atoi(argv[2]);
	if( argv[1][0]>='0' && argv[1][0]<='9' ){
		serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	}else{
		getAddrFromHost(buf, argv[1]);
		serv_addr.sin_addr.s_addr = inet_addr(buf);;
	}

	// Send & Recieve
	gettimeofday(&tv1, NULL);
	memcpy(message, &tv1, sizeof(tv1));
	sendto(sock, message, sizeof(tv1), 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	recvfrom(sock, message, BUFSIZE, 0, (struct sockaddr*)&from_addr, &addr_size);
	gettimeofday(&tv2, NULL);
	close(sock);

	// result
	diff = (tv2.tv_sec + (tv2.tv_usec/1000)*0.001f) - (tv1.tv_sec + (tv1.tv_usec/1000)*0.001f);
	printf("Round-trip time: %.3f ms \n", diff);

	return 0;
}
