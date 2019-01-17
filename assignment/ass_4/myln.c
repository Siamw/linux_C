#include <stdio.h>
#include <unistd.h>
//heyhey
main(int argc, char *argv[])
{
	if (argc != 3)  {//2개 입력하지 않았으면 에러
	fprintf(stderr, "Usage: %s source destinaion\n", argv[0]);
	exit(1);
	}

	if (link(argv[1],argv[2]) < 0)  {//argv[1]에게 argv[2]라는 다른 이름 하나를 더 만들어준다.하드링크이므로 원본파일과 동일한 inode를 가져서 원본파일이 삭제되더라도 여전히 사용 가능하다.
		perror("link");
		exit(1);
	}
}
