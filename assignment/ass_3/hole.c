#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

main()
{
	int fd;
	char ch='\0';

	if((fd=creat("file.hole", 0400))<0){// file.hole을 만들고 접근권한은 0400으로 한다. 실패시 -1을 반환하여 if문 안으로 들어간다.성공시 파일디스크립터를 fd에 저장한다.
			perror("creat");
			exit(1);
	}

	if(lseek(fd, 1023, SEEK_SET)<0){//열린 지정자 fd로부터 offset 1023만큼 위치를 변경한다.위치 변경시 기준점 seek_set(처음)
//리턴값은 시작으로부터 떨어진 byte만큼의 offset
			perror("lseek");
			exit(1);
	}

	write(fd,&ch,1); //fd에 ch를 1바이트만큼 쓴다.

	close(fd);
}


