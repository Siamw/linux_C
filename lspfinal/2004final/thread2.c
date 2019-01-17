#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int Count = 0;

sem_t sem1;
sem_t sem2;
sem_t mutex;

void 
PrintOdd( void* dummy ) 
{
	int i;
	
	for( i = 0; i < 3; i++ ) { 

		if(  sem_wait(&sem1) < 0 ) { 
			perror("sem_wait");
			pthread_exit(NULL);
		}

		if( sem_wait(&mutex) < 0 ) { 
			perror("sem_wait");
			pthread_exit(NULL);
		}
	
		if( Count % 2 == 0 ) 
	 		Count++;

		printf("Odd thread  : %d\n", Count );

		if ( sem_post(&mutex) < 0 ) {
			 perror("sem_post");
			 pthread_exit(NULL);
		}

		if ( sem_post(&sem2) < 0 ) { 
			perror("sem_post");
			pthread_exit(NULL);
		}
	}

}

void 
PrintEven( void* dummy ) 
{
	int i;


	for( i = 0 ; i < 3; i++ ) { 

		if(  sem_wait(&sem2) < 0 ) { 
			perror("sem_wait");
			pthread_exit(NULL);
		}

		if(  sem_wait(&mutex) < 0 ) { 
			perror("sem_wait");
			pthread_exit(NULL);
		}

		if( Count % 2 != 0 )
			Count++;

		printf("Even thread : %d\n", Count );

		if ( sem_post(&mutex) < 0 ) { 
			perror("sem_post");
			pthread_exit(NULL);
		}

		if ( sem_post(&sem1) < 0 ) { 
			perror("sem_post");
			pthread_exit(NULL);
		}
	}

}


main()
{
	pthread_t tid1, tid2;
	
	
	if( ( sem_init( &sem1,0, 1 ) ) < 0 ) {  
		perror("sem_init");	
		exit(1);
	}
	
	if( ( sem_init( &sem2, 0, 0 ) ) < 0 ) { 
		perror("sem_init");
		exit(1);	
	}
	
	if( ( sem_init( &mutex, 0, 1 ) ) < 0 ) { 
		perror("sem_init");
		exit(1);	
	}
		
	if( ( pthread_create( &tid1, NULL, (void*)PrintOdd, (void*)NULL) ) < 0 ) { 
		perror("pthread_create");
		exit(1);
	}

	if( ( pthread_create( &tid2, NULL, (void*)PrintEven, (void*)NULL ) ) < 0 ) { 
		perror("pthread_create");
		exit(1);
	}

	if( ( pthread_join( tid1, NULL ) ) < 0 ) { 
		perror("pthread_join");
		exit(1);
	}

	if( ( pthread_join( tid2, NULL ) ) < 0 ) { 
		perror("pthread_join");
		exit(1);
	}
	

	if( ( sem_destroy(&sem1) ) < 0 ) { 
		perror("sem_destroy");
		exit(1);
	}

	if( ( sem_destroy(&sem2) ) < 0 ) { 
		perror("sem_destroy");
		exit(1);
	}

	if( ( sem_destroy(&mutex) ) < 0 ) { 
		perror("sem_destroy");
		exit(1);
	}

}
