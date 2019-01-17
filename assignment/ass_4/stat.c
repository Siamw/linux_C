#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

main(int argc, char *argv[])
{
	struct stat	statbuf;
	char	*mode;
	int i;

	for (i = 1 ; i < argc ; i++)  {
	printf("%s: ", argv[i]);
	if (lstat(argv[i],&statbuf))  {//argv의 파일 정보를 statbuf에 읽어오는 함수
	perror("lstat");
	continue;
	}
	if (S_ISREG(statbuf.st_mode))//일반 파일인가?
		mode = "regular";
	else if (S_ISDIR(statbuf.st_mode))//디렉토리인가?
		mode = "directory";
	else if (S_ISCHR(statbuf.st_mode))//character device인가?
		mode = "character special";
	else if (S_ISBLK(statbuf.st_mode))//block device인가?
		mode = "block special";
	else if (S_ISFIFO(statbuf.st_mode))//FIFO인가?
		mode = "FIFO";
	else if (S_ISLNK(statbuf.st_mode))//symbolic link인가?
		mode = "symbolic link";
	else if (S_ISSOCK(statbuf.st_mode))//socket인가?
		mode = "socket";

		printf("%s\n", mode);
		printf("\tst_mode = %d\n", statbuf.st_mode);
		printf("\tst_ino = %d\n", statbuf.st_ino);
		printf("\tst_dev = %d\n", statbuf.st_dev);
		printf("\tst_rdev = %d\n", statbuf.st_rdev);
		printf("\tst_nlink = %d\n", statbuf.st_nlink);
		printf("\tst_uid = %d\n", statbuf.st_uid);
		printf("\tst_gid = %d\n", statbuf.st_gid);
		printf("\tst_size = %d\n", statbuf.st_size);
		printf("\tst_atime = %d\n", statbuf.st_atime);
		printf("\tst_mtime = %d\n", statbuf.st_mtime);
		printf("\tst_ctime = %d\n", statbuf.st_ctime);
		printf("\tst_blksize = %d\n", statbuf.st_blksize);
		printf("\tst_blocks = %d\n", statbuf.st_blocks);
	}
}
