#include <stdio.h>

#define MAX 100

main(int argc, char * argv[])
{
    FILE    *fp;
    char    line[MAX];
    int     cntline=0;

    if (argc != 3)  {
        printf("Usage : %s string filename\n", argv[0]);
        exit(1);
    }

    if ( (fp = fopen(argv[2], "rt") ) == NULL) {//세번째 성분 fp에 넣음
        perror("fopen");
        exit(1);
    }

    while (fgets(line, MAX, fp) != NULL)   {//fp의 값 line에 저장
			cntline++;//몇번째 라인인가?
        if (strstr(line, argv[1]))  {//두번째 성분과 line에 같은게 있으면
                printf("%d: %s",cntline, line);//몇번째줄인지, 뭔지 출력
        }
    }

    close(fp);
}

