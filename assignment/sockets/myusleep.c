#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>

		void
myusleep(int secs, int usecs)
{
		struct timeval tm;

		tm.tv_sec = secs;
		tm.tv_usec = usecs;

		if (select(0, (fd_set *)0, (fd_set *)0, (fd_set *)0, &tm) < 0/* select */)  {
				// 영원히 발생되지 않을 이벤트를 저 시간만큼 기다리게 했다...
				// 기다렸다가 빠져나오도록 함 ! 
				perror("select");
				return;
		}
}

main()
{
		printf("Sleep for 1.5 seconds.....\n");
		myusleep(1, 500000);
}
