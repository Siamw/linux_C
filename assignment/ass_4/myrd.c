#include <stdio.h>
#include <unistd.h>

main(int argc, char *argv[])
{
	if (argc != 2)  {//하나 입력받지 않으면 에러
	fprintf(stderr, "Usage: %s dirname\n", argv[0]);
	exit(1);
	}

	if (rmdir(argv[1]) < 0)  {//argv[1] 디렉토리를 지운다.
	perror("rmdir");
	exit(1);
	}
}
