#include <stdio.h>
#include <unistd.h>

#define MAX_BUF 1024

long filesize(FILE *fp)
{
	long cur, size;

	cur=ftell(fp);//ftell 현위치 반환
	fseek(fp, 0L, SEEK_END);//fp, 첫위치 long int 0으로  정해쥼 , 끝으로 감
	size=ftell(fp);//끝 위치 사이즈로 반환
	fseek(fp, cur, SEEK_SET);//fp, 처음에 cur위치로 fp위치 이동
	return(size);
}

main(int argc, char *argv[])
{
	FILE *src, *dst1, *dst2;
	char buf[MAX_BUF];
	int count, size;

	if(argc !=4){//3개 입력 안받앗으면 에러 출력
		fprintf(stderr, "Usage : %s source dest1 dest2\n", argv[0]);
		exit(1);
		}

	if((src = fopen(argv[1], "rb"))==NULL){//첫번째꺼 이진모드로 읽기만 가능하게 src에 염. null이면 에러
		perror("fopen");
		exit(1);
		}
	
	if((dst1 = fopen(argv[2], "wb"))==NULL){//이진모드로 쓰기만 가능하게 dst1에 두번째 입력값으로 생성. null이면 에러
		perror("fopen");
		exit(1);
		}

	if((dst2 = fopen(argv[3], "wb")) ==NULL){//세번째거 이름으로 위랑 마찬가지로 생성
		perror("fopen");
		exit(1);
		}

	size = filesize(src)/2;//src의 파일사이즈의 절반을 size로 함

	while (size>0) {//size가 0될때까지
		count = (size>MAX_BUF) ? MAX_BUF :size;//maxbuf랑 size중에 작은값을 count에 넣음
		fread(buf, 1, count, src);//src에서 1씩 count만큼 buf에 저장
		fwrite(buf, 1, size, dst1);//size 항목까지, 1~size까지 바이트를 buffer에서 dst1까지 쓴다.
		size -= count;
		}

	while ((count = fread(buf, 1, MAX_BUF, src))>0){//src에서 1씩 max_buf까지 buf에 읽어오고 그 수를 count에 저장
		fwrite(buf, 1, size, dst2);//dst2에 1식 size만큼 buf를 저장
		}

	fclose(src);
	fclose(dst1);
	fclose(dst2);

}
