#include <stdio.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

main(int argc, char *argv[])
{
int fdin, fdout;
char *src, *dst;
struct stat statbuf;

if (argc != 3)  {
fprintf(stderr, "Usage: %s source destination\n", argv[0]);
exit(1);
}

if ((fdin = open(argv[1], O_RDONLY)) < 0)  {
perror("open");
exit(1);
}
if ((fdout = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0644)) < 0)  {
perror("open");
exit(1);
}

//size 알아오기 위함.. data statbuf에 가져옴
if (fstat(fdin, &statbuf) < 0)  {
perror("fstat");
exit(1);
}

//첫번째 파일은 카피할 파일 사이즈 만큼
//두번째 파일도 같은 파일 사이즈 크기로 만들어놔야 함
//그렇게 하기 위한 과정.. 포인터를 파일사이즈-1 만큼 옮겨놓음
if (lseek(fdout, statbuf.st_size-1, SEEK_SET) < 0)  {
perror("lseek");
exit(1);
}
write(fdout, "", 1); //실제로는 null character 1byte들어있다고 생각....

//포인터변수 통한 접근 위함!!!!!!!!!!!!

if ((src = mmap(0, statbuf.st_size, PROT_READ, MAP_SHARED, fdin, 0)) 
== (caddr_t) -1)  {
perror("mmap");
exit(1);
}

if ((dst = mmap(0, statbuf.st_size, PROT_WRITE, MAP_SHARED, fdout, 0)) 
== (caddr_t) -1)  {
perror("mmap");
exit(1);
}

//운영체제에서 읽으라고 요청
//systemcall
memcpy(dst, src, statbuf.st_size);

close(fdin);
close(fdout);
}
