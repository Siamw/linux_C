#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include "rwp.h"

BoundedBufferType	Buf;

		void
ThreadUsleep(int usecs)
{
		pthread_cond_t	cond;
		pthread_mutex_t	mutex;
		struct timespec	ts;
		struct timeval	tv;

		if (pthread_cond_init(&cond, NULL) < 0)  {
				perror("pthread_cond_init");
				pthread_exit(NULL);
		}

		if (pthread_mutex_init(&mutex, NULL) < 0)  {
				perror("pthread_mutex_init");
				pthread_exit(NULL);
		}

		gettimeofday(&tv, NULL);
		ts.tv_sec = tv.tv_sec + usecs/1000000;
		ts.tv_nsec = (tv.tv_usec + (usecs%1000000)) * 1000;

		if (ts.tv_nsec >= 1000000000)  {
				ts.tv_nsec -= 1000000000;
				ts.tv_sec++;
		}

		if (pthread_mutex_lock(&mutex) < 0)  {
				perror("pthread_mutex_lock");
				pthread_exit(NULL);
		}
		if (pthread_cond_timedwait(&cond, &mutex, &ts) < 0)  {
				perror("pthread_cond_timedwait");
				pthread_exit(NULL);
		}

		if (pthread_cond_destroy(&cond) < 0)  {
				perror("pthread_cond_destroy");
				pthread_exit(NULL);
		}
		if (pthread_mutex_destroy(&mutex) < 0)  {
				perror("pthread_mutex_destroy");
				pthread_exit(NULL);
		}
}

		void
Writer(int id)
{
		int	i, data;

//		printf("Producer: Start.....\n");

		for (i = 0 ; i < NLOOPS ; i++)  {
				while (Buf.counter == MAX_BUF) 
						;
				
				printf("Writer %d  writing...\n",id);
				data = (rand()%100)*10000;
				Buf.buf[Buf.in].data = data;
				Buf.in = (Buf.in + 1) % MAX_BUF;
				Buf.counter++;

				ThreadUsleep(data);
		}

//		printf("Producer: Produced %d items.....\n", i);
//		printf("Producer: %d items in buffer.....\n", Buf.counter);

		pthread_exit(NULL);
}

		void
Reader(int id)
{
		int	i, data;

	//	printf("Consumer: Start.....\n");

		for (i = 0 ; i < NLOOPS ; i++)  {
				while (Buf.counter == 0)
						;

				printf("Reader %d  reading...\n",id);
				data = Buf.buf[Buf.out].data;
				Buf.out = (Buf.out + 1) % MAX_BUF;
				Buf.counter--;

				ThreadUsleep((rand()%100)*10000);
		}

	//	printf("Consumer: Consumed %d items.....\n", i);
	//	printf("Consumer: %d items in buffer.....\n", Buf.counter);

		pthread_exit(NULL);
}

main()
{
		pthread_t	wtid[2];
		pthread_t	rtid[3];
		int wid[2];
		int rid[3];
		int p,q;

		srand(0x8888);

	for(p=0;p<2;p++)
	{	if (pthread_create(&wtid[p], NULL, (void *)Writer, (void *)wid[p]) < 0)  {
				perror("pthread_create");
				exit(1);
		}
		wid[p]=p;
	}


	for(q=0;q<3;q++){
		if (pthread_create(&rtid[q], NULL, (void *)Reader, (void *)rid[q]) < 0)  {
				perror("pthread_create");
				exit(1);
		}
	rid[q]=q;
}

	for(p=0;p<2;p++)
		{if (pthread_join(wtid[p], NULL) < 0)  {
				perror("pthread_join");
				exit(1);
			}
		}
	for(q=0;q<3;q++){
		if (pthread_join(rtid[q], NULL) < 0)  {
				perror("pthread_join");
				exit(1);
		}}

	//	printf("Main    : %d items in buffer.....\n", Buf.counter);
}
