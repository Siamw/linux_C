#include <stdio.h>

main(int argc, char *argv[])
{
	if (argc != 3)  {//입력이 2개가 아니면 에러
		fprintf(stderr, "Usage: %s old new\n", argv[0]);
		exit(1);
	}

	if (rename(argv[1],argv[2])<0) {//argv[1] 이름을 argv[2]로 바꾼다.
		perror("rename");
		exit(1);
	}
}
