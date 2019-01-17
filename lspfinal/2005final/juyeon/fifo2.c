#include <stdio.h>
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

	// fname을 가지고 temporary fifo를 만든다.
	sprintf(fname, ".fifo%d", getpid());
	if (mkfifo(fname, 0600) < 0)  {
		perror("mkfifo");
		exit(1);
	}

	// fd로 fname을 연다.
	if ((fd = open(fname, O_RDWR)) < 0)  {
		perror("open");
		exit(1);
	}
	
	// sfd로 SERV_FIFO fifo를 연다.
	if ((sfd = open(myfifo, O_RDWR)) < 0)  {
		perror("open");
		exit(1);
	}

	strcpy(msg.returnFifo, fname);
	sprintf(msg.data, "%s", "Hello");
	// msg내용을 쓴다.
	write(sfd, (char *)&msg, sizeof(msg)); 
	printf("FIFO2 : Sent a message : %s\n", msg.data);

	// msg의 값을 읽어와서 출력한다.
	if ((n = read(fd, (char *)&msg, sizeof(msg))) < 0 )  {
		perror("read");
		exit(1);
	}

	printf("FIFO2 : Received a message : %s\n", msg.data);

	close(fd);
	close(sfd);

	/* Remove temporary FIFO */
	if (remove(fname) < 0)  {
		perror("remove");
		exit(1);
	}
}
