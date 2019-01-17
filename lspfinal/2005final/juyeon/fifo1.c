#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include "fifo.h"

main()
{
	int			fd, cfd, n;
	MsgType		msg;

	// myfifo fifo 만들기
	if (mkfifo(myfifo, 0600) < 0)  {
		if (errno != EEXIST)  {
			perror("mkfifo");
			exit(1);
		}
	}

	// fd으로 fifo를 연다.
	if ((fd = open(myfifo, O_RDWR)) < 0)  {
		perror("open");
		exit(1);
	}

	while (1)  {
		// msg의 내용을 읽어온다.
		if ((n = read(fd, (char *)&msg, sizeof(msg))) < 0)  {
			// interrupt가 수행 중일때 error
			if (errno == EINTR)  {
				continue;
			}
			else  {
				perror("read");
				exit(1);
			}
		}
		printf("FIFO1 : Received a message : %s\n", msg.data);

		// cfd로 fifo을 연다.
		if ((cfd = open(msg.returnFifo, O_WRONLY)) < 0)  {
			perror("open");
			exit(1);
		}
		// msg.returnFifo값이 있을 때
		// msg.data를 만들어 쓴다.
		sprintf(msg.data, "%s", "Hi");
		write(cfd, (char *)&msg, sizeof(msg));
		printf("FIFO1 : Seant a message : %s\n", msg.data);
		close(cfd);

		if (remove(myfifo) < 0)  {
			perror("remove");
			exit(1);
		}
		exit(0);
		
	}
}

