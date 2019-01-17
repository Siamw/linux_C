#include<stdio.h>
#include<unistd.h>
#include "record.h"

void print_record(Record *rp)
{
	puts(rp->stud);//rp record 의 stud를 출력한다.
	puts(rp->num);//rp record의 num을 출력한다.
	puts(rp->dept);//rp record의 dept를 출력한다.
}

main(int argc, char *argv[])
{
	FILE *fp;
	Record rec;

	if(argc!=2){//길이가 2가 아니면 에러메세지 출력
		fprintf(stderr, "Usage: %s file\n", argv[0]);
		exit(1);
		}

	if((fp = fopen(argv[1], "r+b")) == NULL){//fp에 argv1을 읽고 쓰기 위해 연다.
		perror("fopen");// null인 경우 에러 !
		exit(1);
		}

	printf("----Ordered Record List----\n");

	while(fread(&rec, sizeof(rec),1,fp))//rec의 사이즈만큼 1개씩 fp값을 읽고 rec에 저장한다.
	{print_record(&rec);}

	rewind(fp);//fp의 위치 지정자를 맨 처음으로 설정한다.
	getchar();//문자입력

	printf("----Shuffled Record List (3,6,2,4,1,5)----\n");

	fseek(fp, sizeof(rec)*2L, SEEK_SET);//3번째로 보내기 위해 size 의 2배만큼 이동을 한다.
	fread(&rec, sizeof(rec),1,fp);//rec에 fp를 rec사이즈만큼 하나를 저장한다.
	print_record(&rec);//print

	fseek(fp, sizeof(rec)*5L, SEEK_SET);//파일 시작점에서 6번째 rec 위치로 간다.
	fread(&rec, sizeof(rec),1,fp);//위와 같다. 아래도 마찬가지
	print_record(&rec);//위와 같다. 아래도 마찬가지
	
	fseek(fp, sizeof(rec)*1L, SEEK_SET);//2번째로 간다
	fread(&rec, sizeof(rec),1,fp);
	print_record(&rec);
	
	fseek(fp, sizeof(rec)*3L, SEEK_SET);//4번째로 간다
	fread(&rec, sizeof(rec),1,fp);
	print_record(&rec);
	
	fseek(fp, sizeof(rec)*0L, SEEK_SET);//첫번째로 간다
	fread(&rec, sizeof(rec),1,fp);
	print_record(&rec);
	
	fseek(fp, sizeof(rec)*4L, SEEK_SET);//5번째로 간다
	fread(&rec, sizeof(rec),1,fp);
	print_record(&rec);


	printf("----Updated Record List----\n");

	fseek(fp, sizeof(rec)*2L, SEEK_SET);//세번째 rec위치로 간다 
	fread(&rec, sizeof(rec),1,fp);//현재 fp 위치에서 rec사이즈 하나만큼 rec에 저장한다.
	strcpy(rec.dept, "Movie");//현재 rec의 dept를 Movie로 바꾼다.
	fseek(fp, sizeof(rec)*2L, SEEK_SET);//
	fwrite(&rec, sizeof(rec), 1, fp);
// 
	fseek(fp, sizeof(rec)*5L, SEEK_SET);
	fread(&rec, sizeof(rec), 1, fp);
	strcpy(rec.dept, "Baseball");
	fseek(fp, sizeof(rec)*5L, SEEK_SET);
	fwrite(&rec, sizeof(rec), 1, fp);

	rewind(fp);
	while(fread(&rec, sizeof(rec), 1, fp)){
		print_record(&rec);
		}

		fclose(fp);

}
