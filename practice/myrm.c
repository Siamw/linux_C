#include <stdio.h>

main(int argc, char *argv[])
{
	int i;

	if (argc == 1)  {//아무런 입력이 없다면, 에러
	fprintf(stderr, "Usage: %s filename\n", argv[0]);
	exit(1);
	}

	for (i = 1 ; i < argc ; i++)  {//입력한 모든 파일들에 대하여
		if (remove(argv[i])<0)  {//입력한 파일을 지운다.
			perror("remove");
			exit(1);
		}
	}
}
