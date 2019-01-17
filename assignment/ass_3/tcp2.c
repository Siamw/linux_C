#include <stdio.h>

#define MAX_BUF 256

main(int argc, char *argv[])
{
	FILE *src, *dst;
	char buf[MAX_BUF];

	if(argc !=3){//2개 입력 안받았으면 에러
		fprintf(stderr, "Usage: %s source destination\n", argv[0]);
		exit(1);
		}

	if ((src = fopen(argv[1], "rt")) == NULL) {//첫번째로 입력한거 읽을 수만 있게 열어서 src에 저장하고 null이면 에러출력
		perror("fopen");
		exit(1);
		}

	if ((dst = fopen(argv[2], "wt")) == NULL){//두번째 입력한 이름으로 쓸 수 있게 파일을 만들어서 dst로 지정, null이면 에러 출력
		perror("fopen");
		exit(1);
		}

	while(fgets(buf, MAX_BUF, src)!=NULL){//src에서 한줄씩 최대 max_buf-1만큼 buf에 불러온다
		fputs(buf,dst);//불러온걸 dst에 저장
		}

	fclose(src);
	fclose(dst);

	}

	
