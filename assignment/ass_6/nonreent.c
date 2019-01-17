#include <stdio.h>
#include <signal.h>
#include <pwd.h>

void MyAlarmHandler(int signo)
{
	struct passwd *rootptr;

	signal(SIGALRM, MyAlarmHandler);
	alarm(1);

	printf("in signal handler\n");

	if ((rootptr = getpwnam("root")) == NULL)  {//root의 정보 저장
		perror("getpwnam");
		exit(1);
	}

	return;
}

main()
{
struct passwd *ptr;

signal(SIGALRM, MyAlarmHandler);//sigalarm실행시 핸들러 실행
alarm(1);

	for ( ; ; )  {
		if ((ptr = getpwnam("lsp49")) == NULL)  {//내 정보 가리키는 ptr
		perror("getpwnam");
		exit(1);
		}

		if (strcmp(ptr->pw_name, "lsp49") != 0)  {//값 다르면 에러
			printf("return value corrupted!, pw_name = %s\n", ptr->pw_name);
			exit(0);
		}
	}
}
