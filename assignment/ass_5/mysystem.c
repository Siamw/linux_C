#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int mysystem(char* cmd)
{
	pid_t pid;  // 자식 프로세스의 id를 기록
	int status; // 자식 프로세스가 종료될때의 반환값을 저장
	char** argv; // 명령의 인수 배열
	int i, argc=1;


/* Tokenizing */
	for(i=0; cmd[i]; i++){  // 인수의 갯수 카운트
		if( cmd[i]==' ' )
		argc++;
	}
	argv = (char**)malloc(argc+1);  // 인수 배열 할당
	argv[0] = strtok(cmd, " ");
	for(i=1; i<argc; i++){
		argv[i] = strtok(NULL, " ");
	}
	argv[i] = NULL;


/* Run cmd */
	if( (pid=fork()) < 0 ){
		perror("fork");
		exit(1);
	}
	else if ( pid==0 ){  // child
		if( execvp(argv[0], argv) < 0){  // 인수 배열을 이용해 명령 실행
			perror("execvp");
			exit(1);
		}
	}
	else {  // parent
		waitpid(pid, &status, NULL);
	}


/* Release */
//free( argv );
	return status;
}

int main()
{
	int status;
	char cmd[] = "date; ls -al";

	printf("Running.. \"%s\" \n\n", cmd);

	if( (status = mysystem(cmd)) < 0 ){
		perror("mysystem");
		exit(1);
	}

	printf("\nexit status = %d\n", status);

	return 0;
}

