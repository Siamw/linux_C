#include <stdio.h>

#define MAX_BUF 256

main(int argc, char *argv[])
{
	FILE *fp;
	char buf[MAX_BUF];
	int line;

	if(argc !=2){//argc가 2가 아니면 에러
		printf("Usage: %s filename\n", argv[0]);
		exit(1);
	}

	if((fp=fopen(argv[1], "rt"))==NULL){//입력해준 첫번째 성분을 텍스트로 읽기만 가능하도록 연다.
			perror("fopen");
			exit(1);
	}

	line = 1;
	while(fgets(buf, MAX_BUF, fp)){//fp에서 한줄씩 또는 문자 수 maxbuf-1일때 까지 읽어서 buf에 저장하고 끝에 null문자 추가
		printf("%4d: %s", line++, buf);//buf 한줄씩 출력~~
		}

		fclose(fp);
			
}
