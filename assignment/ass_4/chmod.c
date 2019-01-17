#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

main()
{
	struct stat statbuf;

	if (stat("bar", &statbuf) < 0)  {//bar의 상태를 statbuf에 받아온다
	perror("stat");
	exit(1);
	}

	if (chmod("bar", (statbuf.st_mode & ~S_IWGRP) | S_ISUID) < 0)  {
	//bar의 상태를 현재 상태에서 S_IWGRP,그룹에 대한 쓰기권한만 끈다. 그러고 S_ISUID, 실행을위해 사용자 id를 설정한다. 	
	perror("chmod");
	exit(1);
	}

	/* S_IRUSR, S_IWUSR, S_IRGRP, S_IROTH : ON */
	if (chmod("foo", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH )<0)  {
	//foo의 상태를 유저 읽기권한, 쓰기권한, 그룹에게 읽기권한, 다른사람에게 읽기권한을 해준다.
	perror("chmod");
	exit(1);
	}
}
