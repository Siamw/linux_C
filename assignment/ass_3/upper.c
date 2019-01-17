#include <stdio.h>

#define MAX_BUF 256

void upper_string(char s[])
{
	int c=0;

	while(s[c] != '\0'){//char의 성분이 null이 아니고
		if(s[c]>= 'a' && s[c] <= 'z'){//소문자 a~z 사이의 글이면
			s[c]=s[c]-32;//대문자로 바꾸어준다.
		}
		c++;//다음글자로
	}
}
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
		upper_string(buf);
		printf("%4d: %s", line++, buf);//buf 한줄씩 출력~~
		}

		fclose(fp);
			
}
