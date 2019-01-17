#include <stdio.h>
#include <unistd.h>

#define MAX_BUF 256

main(int argc, char *argv[])
{
	char buf[MAX_BUF];

	if (getcwd(buf, MAX_BUF)==NULL)  {//현재 작업 디렉토리의 이름을 max buf만큼 길이로 buf에 복사
		perror("getcwd");
		exit(1);
	}

	printf("%s\n", buf);
}
