#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

main()
{
	umask(0);
	if (creat("bar", S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH) < 0)  {
	//bar를 사용자에게 읽기권한|쓰기권한|그룹에게 읽기권한|쓰기권한|기타사용자 읽기권한|쓰기권한 을 주어 만든다.
	perror("creat");
	exit(1);
	}

	umask(S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
	//사용자 읽기권한, 쓰기권한, 기타사용자 읽기권한, 쓰기권한으로 디폴트값을 지정해준다.

	if (creat("foo", S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH) < 0)  {
	//foo 또한 bar와같은 권한을 주어 만든다.
	perror("creat");
	exit(1);
	}
}
