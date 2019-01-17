#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define ARRAY_SIZE 40000
#define MALLOC_SIZE 100000
#define SHM_SIZE 100000
#define SHM_MODE (SHM_R | SHM_W)

char Array[ARRAY_SIZE];

main()
{
int shmid;
char *ptr, *shmptr;

if ((ptr = (char *)malloc(MALLOC_SIZE)) == NULL)  { //포인터가 동적 메모리 할당
perror("malloc");
exit(1);
}

if ((shmid = shmget(IPC_PRIVATE, SHM_SIZE, SHM_MODE)) < 0)  {
// IPC_Private, size, mode
perror("shmget");
exit(1);
}
if ((shmptr = shmat(shmid, 0, 0)) == (void *) -1)  { //attach, 아무데나 할당해줘라 ! 
perror("shmat");
exit(1);
}

printf("Array[] from %x to %x\n", &Array[0], &Array[ARRAY_SIZE]);//array 전역변수 출력
printf("Stack around %x\n", &shmid);// shared memory id 의 주소 : local 변수이므로 stack에 저장
printf("Malloced from %x to %x\n", ptr, ptr+MALLOC_SIZE);// pointer가 가리키는곳 : heap
printf("Shared memory attached from %x to %x\n", shmptr, shmptr+SHM_SIZE); // shared memory 는 heap위에 할당되어 있다. 


if (shmdt(shmptr) < 0)  {
perror("shmdt");
exit(1);
}

//할 필요는 없지만,, 강조 -- shared memory쓰면 꼭 지워라 ~~
if (shmctl(shmid, IPC_RMID, 0) < 0)  {
perror("shmctl");
exit(1);
}
}


