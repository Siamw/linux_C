#include <stdio.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include "synclib.h"

#define NLOOPS 10
#define SIZE sizeof(long)


int update(long *ptr)
{
	return ((*ptr)++);
}

main()
{
int fd, i, counter;
pid_t pid;
caddr_t area;

//
if ((fd = open("/dev/zero", O_RDWR)) < 0)  {
perror("open");
exit(1);
}

//mmap ->shared memory가 할당된다. 나만 쓸 수 있다.
//fork하면 자식하고 나하고는 쓸 수 있기 때문에 그런 용도로 사용한다.
if ((area = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0))
== (caddr_t) -1)  {
perror("mmap");
exit(1);
}
close(fd);

TELL_WAIT();
if ((pid = fork()) < 0)  {
perror("fork");
exit(1);
}
else if (pid > 0)  {
for (i = 0 ; i < NLOOPS ; i += 2)  {
if ((counter = update((long *) area)) != i)  {
fprintf(stderr, "Counter mismatch\n");
exit(1);
}
printf("Parent: counter=%d\n", counter);
TELL_CHILD();
WAIT_CHILD();
}
}
else  {
for (i = 1 ; i < NLOOPS ; i += 2)  {
WAIT_PARENT();
if ((counter = update((long *) area)) != i)  {
fprintf(stderr, "Counter mismatch\n");
exit(1);
}
printf("Child : counter=%d\n", counter);
TELL_PARENT();
}
}
}
