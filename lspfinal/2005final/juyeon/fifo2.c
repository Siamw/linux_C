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

	// fname�� ������ temporary fifo�� �����.
	sprintf(fname, ".fifo%d", getpid());
	if (mkfifo(fname, 0600) < 0)  {
		perror("mkfifo");
		exit(1);
	}

	// fd�� fname�� ����.
	if ((fd = open(fname, O_RDWR)) < 0)  {
		perror("open");
		exit(1);
	}
	
	// sfd�� SERV_FIFO fifo�� ����.
	if ((sfd = open(myfifo, O_RDWR)) < 0)  {
		perror("open");
		exit(1);
	}

	strcpy(msg.returnFifo, fname);
	sprintf(msg.data, "%s", "Hello");
	// msg������ ����.
	write(sfd, (char *)&msg, sizeof(msg)); 
	printf("FIFO2 : Sent a message : %s\n", msg.data);

	// msg�� ���� �о�ͼ� ����Ѵ�.
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
