#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

#define MAX_PATH 256

void JustDoIt(char *path)
{
	DIR *dp;
	struct dirent *dep;
	struct stat statbuf;
	char fullpath[MAX_PATH];

	if ((dp = opendir(path)) == NULL)  {//path directory를 연다
		perror("opendir");
		exit(0);
	}

	printf("\n%s:\n", path);// path출력

	while (dep = readdir(dp))  {//dep에 dp정보 반환
		if (strcmp(".", dep->d_name) == 0 || strcmp("..", dep->d_name) == 0)//현재 디렉토리가 dep의 이름이거나 상위 디렉토리가 dep의 이름이면
			continue;//게속 한다
		printf("%s\n", dep->d_name);//이름 출력
	}


/* rewind */
	rewinddir(dp);//dp와 연관된 파일 포인터를 파일 시작으로 이동

	while (dep = readdir(dp))  {//dep에 dp정보 반환
		if (strcmp(".", dep->d_name) == 0 || strcmp("..", dep->d_name) == 0)
			continue;//현재 디렉토리나 상위티렉토리가 dep의 이름과 같으면
		strcpy(fullpath, path);
		strcat(fullpath, "/");
		strcat(fullpath, dep->d_name);//fullpath를 path/dep->d_name 으로 지정

		if (lstat(fullpath, &statbuf))  {//fullpath의 정보를 statbuf에 저장
			perror("lstat");
			exit(1);
			}

		if (S_ISDIR(statbuf.st_mode))  {//fullpath의 정보를 받은 statbuf의 모드가 디렉토리라면
			JustDoIt(fullpath);//현재 pullpath에 대해서 위의 과정을 한번 더 수행
			}
	}

	closedir(dp);
}

main()
{
JustDoIt(".");
}
