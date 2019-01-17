#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>

#define MAX 100

char msg[MAX];

pthread_mutex_t mutex;
pthread_cond_t cond1;

void thread2( void* dummy )
{
     if ( pthread_mutex_lock(&mutex) < 0 )  {
	  perror("pthread_mutex_lock");
	  pthread_exit(NULL);
     }

     strcpy( msg, "Hello");
     printf("%s\n", "test1");

     if ( pthread_cond_signal( &cond1 ) < 0 )  {
	  perror("pthread_cond_signal");
	  pthread_exit(NULL);
     }

     if (pthread_mutex_unlock(&mutex) < 0)  {
	  perror("pthread_mutex_unlock");
	  pthread_exit(NULL);
     }

     printf("after signal thread1\n");

}

void thread1( void* dummy )
{
     int i;

     printf("before lock thread2\n");

     if ( pthread_mutex_lock(&mutex) < 0 )  {
          perror("pthread_mutex_lock");
          pthread_exit(NULL);
     }

     printf("before wait thread2\n");
     if ( pthread_cond_wait(&cond1, &mutex) < 0 )  {
          perror("pthread_cond_timedwait");
          pthread_exit(NULL);
     }

     printf("test1 thread2\n");

     sleep(1);
     puts(msg);

     if ( pthread_mutex_unlock(&mutex) < 0 )  {
	  perror("pthread_mutex_unlock");
	  pthread_exit(NULL);
     }

}

main()
{
     pthread_t tid1, tid2;


     if( pthread_mutex_init(&mutex, NULL) <0 ) {
	  perror("pthread_mutex_init() error");
	  exit(1);
     }

     if( pthread_cond_init(&cond1, NULL) <0 ) {
	  perror("pthread_mutex_init() error");
	  exit(1);
     }


     if ( pthread_create(&tid1, NULL, (void *)thread1, (void *)NULL) < 0 )  {
	  perror("pthread_create");
	  exit(1);
     }

     if ( pthread_create(&tid2, NULL, (void *)thread2, (void *)NULL) < 0 )  {
	  perror("pthread_create");
	  exit(1);
     }

     if ( pthread_join(tid1, NULL) < 0 )  {
	  perror("pthread_join");
	  exit(1);
     }

     if ( pthread_join(tid2, NULL) < 0 )  {
	  perror("pthread_join");
	  exit(1);
     }
     
     pthread_cond_destroy( &cond1 );
     pthread_mutex_destroy( &mutex );

}

