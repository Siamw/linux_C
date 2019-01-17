#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>

char msg[100];

sem_t syncSem, mutexSem;

void 
WriteMessage( void* arg ){

	sem_wait(&mutexSem);
	strcpy( msg, "hello" );
	sem_post(&mutexSem );
	sem_post(&syncSem);

}

void 
ReadMessage( void* arg ) {
	
	sem_wait(&syncSem);
	sem_wait(&mutexSem);
	sleep(1);
	puts( msg );
	sem_post(&mutexSem);
}

main() {

	pthread_t tid1, tid2;

	if( ( sem_init( &syncSem, 0, 0  ) ) < 0 ) {
		perror("sem_init");	
		exit(1);
	}
	
	if( ( sem_init( &mutexSem, 0, 1 ) ) < 0 ) {
		perror("sem_init");
		exit(1);
	}
	
	if ( ( pthread_create( &tid1, NULL, (void*)WriteMessage, (void*)NULL) ) < 0 ){
		perror( "pthread_create");
		exit(1);
	}
	
	if ( ( pthread_create( &tid2, NULL, (void*)ReadMessage, (void*)NULL ) ) < 0 ){ 
		perror( "pthread_create");
		exit(1);
	}

	if( pthread_join( tid1, NULL) < 0 ) {
		perror("pthread_join");
		exit(1);
	}

	if( pthread_join( tid2, NULL ) < 0 ) {
		perror("pthread_join");
		exit(1);
	}
		
	if ( sem_destroy(&syncSem ) < 0 ) {
		perror("sem_destory");
	}	

	if ( sem_destroy(&mutexSem) < 0 ) {
		perror("sem_destroy");
	}	
}

