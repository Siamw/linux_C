#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<signal.h>

int x;

void SigChildHandler(int signo)
{
     exit(0);
}

main()
{
     pid_t pid;
     int i,sum;

     signal(SIGCHLD, SigChildHandler);
     x=0;

     if( (pid = fork() ) < 0) {
	  perror("fork");
	  exit(1);
     }
     else if( pid == 0 ) {
	  for(i=1;i<=10;i++) {
	       sum += i;
	  }
     }
     else {  
	  /* 부모 처리 시 */
	  while(1)
	  {
	       if(x==0) 
		    break;
	       i++;
	  }
     }
     printf("%d\n",i);
}
