#include <stdio.h>

enum { FALSE, TRUE };

void conv(char *fname)
{
	FILE *src, *dst;
	char fdest[40];
	int ch, first;

	if((src=fopen(fname,"rt"))==NULL){//src에 param fname을 텍스트파일형태로 읽기만 가능하게 연다.
		perror("fopen");
		return;
		}
	
	strcpy(fdest, fname);//fdest에 fname을 복사
	strcat(fdest, ".t");//fdest에 .t붙임
	if((dst=open(fdest, "wt"))==NULL){//dst에 fdest를 쓰기가능하게 텍스트 형태로 연다
		perror("fopen");
		return;
		}

	first = TRUE;
	while ((ch = fgetc(src)) != EOF){//src를 ch에 한줄씩 긁어옴
		if(first && ch == '\t'){//first가 참이고 받아온 ch가 tab이면
			fputc(' ', dst);
			fputc(' ', dst);
			fputc(' ', dst);
			fputc(' ', dst);}//dst에 공백 네개를 넣는다.
			else {//아니면
				fputc(ch, dst);//ch를 dst에 넣음
				if(first)//참이면 거짓으로 바꿔줌
					first = FALSE;
				if(ch=='\n')//다음줄로 넘어가야 참으로 바꿔줌
					first = TRUE;
			}
		}

		fclose(src);
		fclose(dst);
}

main(int argc, char *argv[])
{
	while (--argc){//하나하나 다
		conv(argv[argc]);//위에 함수 실행
		}

}
