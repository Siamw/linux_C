#include <stdio.h>
#include <unistd.h>

main(int argc, char *argv[])
{
	if (argc != 3){
		printf("argv error");
		exit(1);
	}
	int a = atoi(argv[1]);//두번째 arg a
	int b= atoi(argv[2]);//세번째 arg b

	printf("%d+%d=%d\n",a,b,a+b);//더한것 출력
}
