#include <stdio.h>

#define MAX_BUF 1024

main(int argc, char *argv[])
{
	FILE *src1, *src2, *dst;
	char buf[MAX_BUF];
	int count;

	if(argc !=4){//입력 세개 아니면 에러
		fprintf(stderr, "Usage : %s source1 source2 dest\n", argv[0]);
	}

	if((src1 = fopen(argv[1],"rb")) ==NULL){//첫번째꺼 이진모드로 읽기만 가능하게 src1에 연다. null이면 에러
		perror("fopen");
		exit(1);
		}

	if((src2 = fopen(argv[2], "rb")) == NULL){//두번째거 이진모드로 읽기만 가능하게 src2에 염. null이면 에러
		perror("fopen");
		exit(1);
		}

	if((dst = fopen(argv[3], "wb")) ==NULL){//세번째꺼 이름으로 쓰기만 가능한 이진모드파일을 생성=dst. null이면 에러
		perror("fopen");
		exit(1);
		}

	while (count=fread(buf, 1, MAX_BUF, src1)>0){//src1에서 1씩 max_buf만큼 buf에 저장,count에 길이 저장
		fwrite(buf,1,count,dst);//dst에 1씩  count만큼 buf에 있는걸 저장
		}

	while ( count=fread(buf, 1, MAX_BUF, src2)>0){//src2에서 1씩 max_buf만큼 buf에 저장, count에 길이 저장
		fwrite(buf,1,count,dst);//dst에 1씩 count만큼 buf에 있는걸 저장
		}

	fclose(src1);
	fclose(src2);
	fclose(dst);
}

