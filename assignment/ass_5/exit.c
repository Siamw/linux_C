#include <stdio.h>
#include <stdlib.h>

void myexit1()
{
	printf("first exit handler\n");
}

void myexit2()
{
	printf("second exit handler\n");
}

main()
{
/* Add myexit2 to exit functions */

	if (atexit(myexit2) != 0)  {// atexit 함수는 , 시스템이 정상 프로그램 종료 시 호출하는 함수를 레코드 한다.
								// 정상적으로 작동되지 않으면 에러를 출력한다.
		perror("atexit");
		exit(1);
	}

	if (atexit(myexit1) != 0)  {
		perror("atexit");
		exit(1);
	}

	if (atexit(myexit1) != 0)  {
		perror("atexit");
		exit(1);
	}

	printf("main is done\n");
}
