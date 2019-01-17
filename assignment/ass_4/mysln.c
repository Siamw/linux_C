#include <stdio.h>
#include <unistd.h>
//hey

main(int argc, char *argv[])
{
	if (argc != 3)  {//2개 파일을 입력받지 않으면 에러
		fprintf(stderr, "Usage: %s source destinaion\n", argv[0]);
		exit(1);
	}

	if (symlink(argv[1],argv[2])<0)  {//argv[2]가 argv[1]파일의 이름을 가리키도록 한다.1이 사라지면 2는 기능을 하지 못한다.
		perror("link");
		exit(1);
	}
}
