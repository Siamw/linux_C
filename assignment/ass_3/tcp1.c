#include <stdio.h>

main(int argc, char *argv[])
{
	FILE *src, *dst;
	int ch;

	if( argc != 3){//입력 2개 아니면 에러
		fprintf(stderr, "Usage: %s source destination\n", argv[0]);
		exit(1);
	}

	if((src=fopen(argv[1], "rt")) ==NULL){//첫번째꺼 읽기만 가능한 텍스트 파일로 읽어서 src에 저장. null이면 에러출력
		perror("fopen");
		exit(1);
	}

	if((dst = fopen(argv[2], "wt")) ==NULL){//두번째꺼 이름으로 쓰기만 가능한 텍스트파일 생성하여 dst에 저장한다.null이면 에러 출력
		perror("fopen");
		exit(1);
	}

	while((ch=fgetc(src))!=EOF){//src가 끝날 때 까지 ch에 저장
		fputc(ch, dst);//ch에 저장한걸 dst에 넣음
		}

		fclose(src);
		fclose(dst);

}
