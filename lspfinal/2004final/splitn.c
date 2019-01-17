#include <stdio.h>
#include <unistd.h>

#define	MAX_BUF	1024

// filesize return �Լ�
long
filesize(FILE *fp)
{
	long	cur, size;

    // ������ fp pointer�� ��ġ�� return �Ѵ�. 
	cur = ftell(fp);
    // ������ file ������ �̵��Ѵ�.
	fseek(fp, 0L, SEEK_END);
    // size�� ũ�⸦ �ľ��Ѵ�.
	size = ftell(fp);
    // ���� file�� ���������� �ʱ��� fp pointer�� ��ġ�� ����.
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

        // file pointer src�� file�� open�Ѵ�.
	if ((src = fopen(argv[1], "rb")) == NULL)  {
		perror("fopen");
		exit(1);
	}

	sprintf(file_name1, "%s%s", argv[1], ".1");
	sprintf(file_name2, "%s%s", argv[1], ".2");
	sprintf(file_name3, "%s%s", argv[1], ".3");

        // file pointer dst1�� file�� open�Ѵ�.
	if ((dst1 = fopen(file_name1, "wb")) == NULL)  {
		perror("fopen");
		exit(1);
	}

        // file pointer dst2�� file�� open�Ѵ�.
	if ((dst2 = fopen(file_name2, "wb")) == NULL)  {
		perror("fopen");
		exit(1);
	}

	// file pointer dst3�� file�� open�Ѵ�.
	if ((dst3 = fopen(file_name3, "wb")) == NULL)  {
		perror("fopen");
		exit(1);
	}

        // src�� open file size 1/3  ũ��
	size = filesize(src) / 3;

        // src�� open file size�� �� 1/3 ũ��
        // dst1���� open file buf�� count ��ŭ ����. 
	while (size > 0)  {
		count = (size > MAX_BUF) ?  MAX_BUF : size;
		fread(buf, 1, count, src); 
		fwrite(buf, 1, count, dst1); 
		size -= count;
	}

       // src�� open file size�� �� �� 1/3 ũ��
       // dst2���� open file buf�� count ��ŭ ����.
	size = filesize(src) / 3;
	while (size > 0)  {
		count = (size > MAX_BUF) ?  MAX_BUF : size;
		fread(buf, 1, count, src);
		fwrite(buf, 1, count, dst2);
		size -= count;
	}
	
	// src�� open file size�� �� �� 1/3 ũ��
	// dst3���� open file buf�� count ��ŭ ����.
	while ((count = fread(buf, 1, MAX_BUF, src)) > 0)  {
		fwrite(buf, 1, count, dst3);
	}

	fclose(src);
	fclose(dst1);
	fclose(dst2);
	fclose(dst3);
}

