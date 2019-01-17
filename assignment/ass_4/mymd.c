#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

main(int argc, char *argv[])
{
	if (argc != 2)  {//성분하나 입력안받으면 에러
		fprintf(stderr, "Usage: %s dirname\n", argv[0]);
		exit(1);
	}

/* 755 permission */
	if (mkdir(argv[1],0755)<0)  {//0755권한을 주며 argv[1]파일 생성
		perror("mkdir");
		exit(1);
	}
}
