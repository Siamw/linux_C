#include <stdio.h>
#include <unistd.h>

main(int argc, char *argv[])
{
	if (argc != 2)  {
		fprintf(stderr, "Usage: %s dirname\n", argv[0]);
		exit(1);
	}

	if (chdir(argv[1])<0)  {//argv[1]로 디렉토리 경로를 변경한다.
		perror("chdir");
		exit(1);
	}
}
