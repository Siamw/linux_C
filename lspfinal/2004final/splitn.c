#include <stdio.h>
#include <unistd.h>

#define	MAX_BUF	1024

// filesize return 함수
long
filesize(FILE *fp)
{
	long	cur, size;

    // 현재의 fp pointer의 위치를 return 한다. 
	cur = ftell(fp);
    // 현재의 file 끝으로 이동한다.
	fseek(fp, 0L, SEEK_END);
    // size의 크기를 파악한다.
	size = ftell(fp);
    // 현재 file의 시작점에서 초기의 fp pointer의 위치로 간다.
	fseek(fp, cur, SEEK_SET);
	return(size);
}

main(int argc, char *argv[])
{
	FILE	*src, *dst1, *dst2, *dst3;
	char	buf[MAX_BUF];
	int		count, size;
	char 	file_name1[10];
	char	file_name2[10];
	char 	file_name3[10];

	if (argc != 2)  {
		fprintf(stderr, "Usage: %s source\n", argv[0]);
		exit(1);
	}

        // file pointer src로 file을 open한다.
	if ((src = fopen(argv[1], "rb")) == NULL)  {
		perror("fopen");
		exit(1);
	}

	sprintf(file_name1, "%s%s", argv[1], ".1");
	sprintf(file_name2, "%s%s", argv[1], ".2");
	sprintf(file_name3, "%s%s", argv[1], ".3");

        // file pointer dst1로 file을 open한다.
	if ((dst1 = fopen(file_name1, "wb")) == NULL)  {
		perror("fopen");
		exit(1);
	}

        // file pointer dst2로 file을 open한다.
	if ((dst2 = fopen(file_name2, "wb")) == NULL)  {
		perror("fopen");
		exit(1);
	}

	// file pointer dst3로 file을 open한다.
	if ((dst3 = fopen(file_name3, "wb")) == NULL)  {
		perror("fopen");
		exit(1);
	}

        // src로 open file size 1/3  크기
	size = filesize(src) / 3;

        // src로 open file size의 앞 1/3 크기
        // dst1으로 open file buf에 count 만큼 쓴다. 
	while (size > 0)  {
		count = (size > MAX_BUF) ?  MAX_BUF : size;
		fread(buf, 1, count, src); 
		fwrite(buf, 1, count, dst1); 
		size -= count;
	}

       // src로 open file size의 그 담 1/3 크기
       // dst2으로 open file buf에 count 만큼 쓴다.
	size = filesize(src) / 3;
	while (size > 0)  {
		count = (size > MAX_BUF) ?  MAX_BUF : size;
		fread(buf, 1, count, src);
		fwrite(buf, 1, count, dst2);
		size -= count;
	}
	
	// src로 open file size의 그 담 1/3 크기
	// dst3으로 open file buf에 count 만큼 쓴다.
	while ((count = fread(buf, 1, MAX_BUF, src)) > 0)  {
		fwrite(buf, 1, count, dst3);
	}

	fclose(src);
	fclose(dst1);
	fclose(dst2);
	fclose(dst3);
}

