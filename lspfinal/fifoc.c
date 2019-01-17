/* fifoc.c : FIFO 클라이언트 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include "fifo.h"


main()
{
	char		fname[MAX_FIFO_NAME];
	int			fd, sfd, n;
	MsgType		msg;

	sprintf(fname, ".fifo%d", getpid());
	if (mkfifo(fname, 0600) < 0)  {  // 클라이언트 FIFO 파일 생성
		perror("mkfifo");
		exit(1);
	}

	if ((fd = open(fname, O_RDWR)) < 0)  {  // 클라이언트 FIFO 파일 오픈
		perror("open");
		exit(1);
	}
	if ((sfd = open(SERV_FIFO, O_RDWR)) < 0)  {  // 서버 FIFO 파일 오픈
		perror("open");
		exit(1);
	}

	strcpy(msg.returnFifo, fname);
	sprintf(msg.data, "This is a request from %d.", getpid());
	write(sfd, (char *)&msg, sizeof(msg));
	printf("Sent a request.....");

	if ((n = read(fd, (char *)&msg, sizeof(msg))) < 0)  {
		perror("read");
		exit(1);
	}

	printf("Received reply: %s\n", msg.data);

	close(fd);
	close(sfd);

	if (remove(fname) < 0)  {
		perror("remove");
		exit(1);
	}
}

