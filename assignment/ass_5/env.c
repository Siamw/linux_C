#include <stdio.h>

main(int argc, char *argv[], char *envp[])
{
	int i;
	char **p;
	extern char **environ;

	printf("List command-line arguments\n");
	
	for (i = 0 ; i < argc ; i++)  {//command line 명령 모두 출력
		printf("%s\n", argv[i]);
	}
//
	printf("\n");
	printf("List environment variables from environ variable\n");
	for (p = environ ; *p != NULL ; p++)  {//environ 환경변수 모두 출
		printf("%s\n", *p);
	}

	printf("\n");
	printf("List environment variables from envp variable\n");
	
	for (p = envp ; *p != NULL ; p++)  {//envp 환경변수 모두 출
		printf("%s\n", *p);
	}
	
}
