#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_BUF 128

main()
{
		int n, fd1[2], fd2[2];
		pid_t pid;
		char buf[MAX_BUF];

		if ( pipe(fd1)<0 || pipe(fd2)<0  ){
				perror("pipe");
				exit(1);
		}

		if ((pid = fork()) < 0)  {
				perror("fork");
				exit(1);
		}
		else if (pid == 0)  {
				close(fd1[1]);  // 파이프1 입구 닫음
				close(fd2[0]);  // 파이프2 출구 닫음
				printf("Child : Wait for parent to send data\n");
				if ((n = read(fd1[0], buf, MAX_BUF)) < 0)  {  // 파이프1 출구로 부터 데이터 읽어들임
						perror("read");
						exit(1);
				}
				printf("Child : Received data from parent: ");
				fflush(stdout);
				write(STDOUT_FILENO, buf, n);  // STDOUT으로 버퍼 내용 출력

				strcpy(buf, "Hello, World!\n");
				printf("Child: Send data to parent\n");
				write(fd2[1], buf, strlen(buf)+1);  // 파이프2 입구로 버퍼내용 출력
		}
		else  {
				close(fd1[0]);  // 파이프1 출구 닫음
				close(fd2[1]);  // 파이프2 입구 닫음
				strcpy(buf, "Hello, World!\n");
				printf("Parent: Send data to child\n");
				write(fd1[1], buf, strlen(buf)+1);  // 파이프1 입구로 버퍼내용 출력

				printf("Parent : Wait for child to send data\n");
				if ((n = read(fd2[0], buf, MAX_BUF)) < 0)  {  // 파이프2 출구로 부터 데이터 읽어들임
						perror("read");
						exit(1);
				}
				printf("Parent : Received data from child: ");
				fflush(stdout);
				write(STDOUT_FILENO, buf, n);  // STDOUT으로 버퍼 내용 출력
		}

		exit(0);
}


