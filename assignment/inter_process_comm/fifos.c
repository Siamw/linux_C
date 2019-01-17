#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include "fifo.h"


void
SigIntHandler(int signo)
{
if (remove(SERV_FIFO) < 0)  {// signal을 받으면 지운다.
	perror("remove");
	exit(1);
}
	exit(0);
}


main()
{
	int fd, cfd, n;
	MsgType msg;

if (signal(SIGINT, SigIntHandler) == SIG_ERR)  {//종료시그널
	perror("signal");
	exit(1);
}

if (mkfifo(SERV_FIFO, 0600) < 0)  {//내 아이디로 만든 프로세스만 보낼수있는 fifo
	if (errno != EEXIST)  { //이미 존재해서 에러가 나는경우에는 종료하지 않는다.
		perror("mkfifo");
		exit(1);
	}
}

if ((fd = open(SERV_FIFO, O_RDWR)) < 0)  {//만든 fifo이름, read only로 해도 작동 할 것
	perror("open");
	exit(1);
}

while (1)  {
	if ((n=read(fd, (char*)&msg, sizeof(msg)))<0)  {//open한 file discriptor, char arr buf, max size
		if (errno == EINTR)  {
			continue;
			}
		else  {
			perror("read");
			exit(1);
			}
		}	
	printf("Received request: %s.....", msg.data);//data 출력

	if ((cfd = open(msg.returnFifo,O_WRONLY))<0)  {//refurn fifo  write only open해서 보냄
		perror("open");
		exit(1);
	}

	sprintf(msg.data, "This is a reply from %d.", getpid());//이 메세지는 여기로부터 왔다는것을 알려주는 msg

	/* write */
	write(cfd, (char*)&msg, sizeof(msg));//cfd에 씀

	close(cfd);//안쓸거니까 close
	printf("Replied.\n");
	}
}
