#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <dirent.h>


#define SERV_TCP_PORT 30037

int Sockfd;

void CloseServer()
{
     close(Sockfd);
     printf("\nTCP Server exit.....\n");

     exit(0);
}

main(int argc, char *argv[])
{
     int newSockfd, n, pid;
     int status;
     char msg[64], msg2[1024];
     char newline = '\n';
     int on;	  

     DIR *dp;
     struct dirent *dep;
     
     unsigned int cliAddrLen;
     struct sockaddr_in cliAddr, servAddr;

     // INT핸들러 등록
     signal(SIGINT, CloseServer);

     // socket 생성
     if ( (Sockfd = socket(PF_INET, SOCK_STREAM, 0) ) < 0)  {
          perror("socket");
          exit(1);
     }

     on = 1;
     setsockopt( Sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on) );

     bzero((char *)&servAddr, sizeof(servAddr));
     servAddr.sin_family = PF_INET;
     servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
     servAddr.sin_port = htons(SERV_TCP_PORT);

     // bind
     if ( bind(Sockfd, (struct sockaddr *) &servAddr, sizeof(servAddr) ) < 0 )  {
          perror("bind");
          exit(1);
     }

     listen(Sockfd, 5);

     printf("TCP server started....\n");

     cliAddrLen = sizeof(cliAddr);

     while (1)  {

          if((newSockfd = accept(Sockfd, (struct sockaddr *) &cliAddr, &cliAddrLen)) < 0) {
               perror("accept");
               exit(1);
          }

          if((pid = fork()) < 0) {
               perror("fork");
               exit(1);
          }
          else if(pid == 0) {
               close(Sockfd);

               if ( (n = read(newSockfd, msg, sizeof(msg) ) ) < 0)  {
                    perror("read");
                    exit(1);
               }

	       printf("%s\n",msg);

	       // ls
	       if ((dp = opendir(msg)) == NULL)  {
		    perror("opendir");
		    exit(1);
	       }

               msg2[0] = '\0'; 
	       while ( dep =  readdir(dp))  {
		   if( strcmp ( dep->d_name, "." ) == 0 || 
			             strcmp( dep->d_name, "..") ==  0 ) 
			continue;

		    strcat( msg2, dep->d_name );
		    strcat( msg2, "\n");
	       }

	       if (  write( newSockfd, msg2, strlen(msg2) ) < 0 )  { 
			perror("write");	
			exit(1);
	       }

	       close( newSockfd );
	       exit(0);
	 } 
	 else { 
	  	close(newSockfd);
	 }
     }

}
