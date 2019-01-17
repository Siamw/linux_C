#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_BUF 1024

main(int argc, char *argv[])
{
	int fd1, fd2, count;
	char buf[MAX_BUF];

	if(argc != 3){
			printf("Usage : %s source destination\n", argv[0]);
	}

	if((fd1 = open(argv[1], O_RDONLY))<0) {// argv[1] path 에 있는 값read only open. error(-1)나오면 if문 안에 실행
			perror("open");
			exit(1);
	}

	if((fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644))<0){ // argv[2] path에 있는 값 write only open.	
																	// path name 파일이 존재하지 않으면 파일 생성	
																	// 이미 있는 파일일 경우 WR로 열리면 내용을 모두 지움 
			perror("open");
			exit(1);
	}
	
	while((count=read(fd1, buf, MAX_BUF))>0){//count는 읽어온 바이트 수.fd1를 buf위치에 최대 MAXBUF까지 읽는다
			write(fd2, buf, count); //buf에있는걸 count만큼 fd2에 쓴다.
	}

	close(fd1);
	close(fd2);
}

