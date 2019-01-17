#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include "fifo.h"


void
SigIntHandler(int signo)
{
        if ( remove(FIFO) < 0 )  {
                perror("remove");
                exit(1);
        }

        exit(0);
}


main()
{
        int       fd, n;

        if (signal(SIGINT, SigIntHandler) == SIG_ERR)  {
                perror("signal");
		exit(1);
        }

        /* ��带 0600 ���� �ϴ� FIFO ����. */
        if ( mkfifo(FIFO, 0600) < 0)  {
                if (errno != EEXIST)  {
                        perror("mkfifo");
                        exit(1);
                }
        }

        /* FIFO �� ����. */
        if ( (fd = open(FIFO, O_RDWR)) < 0 )  {
                perror("open");
                exit(1);
        }

        /* read */
        if ( ( n = read ( fd, &data, sizeof(data)  ) ) < 0 )  {
         /* EINT �� ���� �ý��� �� ���� �� ���ͷ�Ʈ�� �ɷ� ������ �ߴܵ�
                       ��쿡 ���ȴ�. */
                    perror("read");
                    exit(1);
               
        }

        printf("FIFO1 : Received a message: %s\n", data );

	strcpy( data , "hi");
	
	sleep(1);
	printf("FIFO1 : Sent a message : %s\n" , data );

        /* write */
        write( fd, data , sizeof(data) );
				

	if ( remove( FIFO )  ) { 
		perror("remove");
		exit(1);
	}

}













