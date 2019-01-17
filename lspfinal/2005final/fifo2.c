#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include "fifo.h"


main()
{
	int			fd, sfd, n;

	/* fname ���� */
	if ((fd = open( FIFO, O_RDWR)) < 0)  {
		perror("open");
		exit(1);
	}

	/* Ŭ���̾�Ʈ fifo  path �Է� */
	strcpy( data, "hello");

	/* write */
	/* server FIFO �� ��� */
	write( fd , &data, sizeof(data) );

	printf("FIFO2 : Sent a message : %s\n", data);
	
	sleep(2);
	/* read */
	/* client FIFO ���� �д´�. */
	if ( ( n = read( fd, &data, sizeof(data) ) ) < 0 )  {
		perror("read");
		exit(1);
	}

	printf("FIFO2 : Received a message : %s\n", data );
 	

}


