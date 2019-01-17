#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

main()
{
	DIR *dp;
	struct dirent *dep;

	if ((dp = opendir(".")) == NULL)  {//현재 디렉토리를 dp에 저장
		perror("opendir");
		exit(0);
	}

	while (dep=readdir(dp))  {//dp의 디렉토리 정보를 dep에 저장
		printf("%s\n", dep->d_name);//디렉토리 안에 있는 모든 파일과 디렉토리 출력
	}

	closedir(dp);
}
