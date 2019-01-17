#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include "fifo.h"


main()
{
	char fname[MAX_FIFO_NAME];
	int fd, sfd, n;
	MsgType msg;

	sprintf(fname, ".fifo%d", getpid());
	if (mkfifo(fname, 0600) < 0)  {//fifo name = char fname
		perror("mkfifo");
		exit(1);
	}

	if ((fd = open(fname, O_RDWR)) < 0)  {//fname을 fd에 리드라이트로 연다
		perror("open");
		exit(1);
	}
	if ((sfd = open(SERV_FIFO, O_RDWR)) < 0)  {//
		perror("open");
		exit(1);
	}

	strcpy(msg.returnFifo, fname);//fname을 return fifo에 넣는다.
	sprintf(msg.data, "This is a request from %d.", getpid());//msg_data에 누구로부터의 pid인지 출력
	/* write */
	write(sfd, (char*)&msg, sizeof(msg));//sfd에 msg를 넣는다
	printf("Sent a request.....");

	if ((n= read(fd, (char*)&msg, sizeof(msg))<0))  {//msg를 fd에 read한다
		perror("read");
		exit(1);
	}

	printf("Received reply: %s\n", msg.data);

	close(fd);
	close(sfd);

	/* Remove temporary FIFO */
	if (remove(fname)<0)  {
		perror("remove");
		exit(1);
	}
}
