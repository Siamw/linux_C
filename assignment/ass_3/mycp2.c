#include <stdio.h>

#define MAX_BUF 1024

main(int argc, char *argv[])
{
	FILE *src, *dst;
	char buf[MAX_BUF];
	int count;

	if(argc !=3){//두개 입력 안받았으면 에러
		fprintf(stderr, "Usage: %s source destination\n", argv[0]);
		exit(1);
		}
	
	if ((src = fopen(argv[1], "rb")) ==NULL) {//첫번째꺼 이진으로 src에 읽기만 가능하게 받아오고 null이면 에러
		perror("fopen");
		exit(1);
		}

	if ((dst = fopen(argv[2], "wb")) ==NULL){//두번째꺼 이름으로 이진파일을 dst에 만든다. null이면 에러
		perror("fopen");
		exit(1);
		}
	
	while((count=fread(buf, 1, MAX_BUF, src))>0){//src에서 1 사이즈의 max_ buf 항목까지 읽어서 buf에 저장하고, 전체 항목수를 count에 저장
		fwrite(buf, 1, count, dst);//buf에서 count(전체 항목 수)까지 1 바이트씩 dst에 쓴다.
		}

		fclose(src);
		fclose(dst);
}
