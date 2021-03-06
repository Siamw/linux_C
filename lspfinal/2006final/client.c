#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define SERV_TCP_PORT 30037

main(int argc, char *argv[])
{
     int sockfd, n;
     struct sockaddr_in servAddr;
     struct hostent *hp;
     char msg[1024];
     int end = 0;
     int on;
     
     if (argc != 3)  {
	  fprintf(stderr, "Usage: %s IPaddress pathname\n", argv[0]);
	  exit(1);
     }

     // socket 생성
     if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)  {
	  perror("socket");
	  exit(1);
     }

     on = 1;
     setsockopt( sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on) );


     bzero((char *)&servAddr, sizeof(servAddr));
     servAddr.sin_family = PF_INET;
     servAddr.sin_port = htons(SERV_TCP_PORT);

     if (isdigit(argv[1][0]))  {
	  servAddr.sin_addr.s_addr = htonl(inet_addr(argv[1]));
     } 
     else  { 
	  if ((hp = gethostbyname(argv[1])) == NULL)  {
	       fprintf(stderr, "Unknown host: %s\n", argv[1]);
	       exit(1);
	  }
	  memcpy(&servAddr.sin_addr, hp->h_addr, hp->h_length);
     }

     // 서버에 접속
     if ( connect(sockfd, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0 )  {
	  perror("connect");
	  exit(1);
     }

     if ( write(sockfd, argv[2], strlen(argv[2]) ) < 0)  {
	  perror("write");
	  exit(1);
     }

     sleep(1);

     if ( (n = read(sockfd, msg, 1024) ) < 0)  {
	  perror("read");
	  exit(1);
     }

     printf("%s", msg);
     close(sockfd);
}


