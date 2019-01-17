#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>


char msg[100];

sem_t syncSem, mutexSem, syncSem2;

void
WriteMessage( void* arg ){

	char inputMsg[100];
	int  n;

	while(1)   { 

        sem_wait(&mutexSem);

	printf("Input:");
	scanf("%s", inputMsg );

	if( ( n = strcmp(inputMsg, "quit") ) == 0 ) { 
		exit(0);
	}

        strcpy( msg, inputMsg  );

       	sem_post(&mutexSem );
        sem_post(&syncSem);
		sem_wait(&syncSem2);

	}
	
	//pthread_exit(NULL);

}

void
ReadMessage( void* arg ) {

	while(1) { 

        sem_wait(&syncSem);
        sem_wait(&mutexSem);
	
	if( strcmp( msg, "quit") == 0 ) { 
		exit(0);
	}

	printf("Output: ");
        sleep(1);
        puts( msg );
        sem_post(&mutexSem);
		sem_post(&syncSem2);

	}
	
}

main() {

        pthread_t tid1, tid2;

        if( ( sem_init( &syncSem, 0, 0  ) ) < 0 ) {
                perror("sem_init");
                exit(1);
        }

        if( ( sem_init( &syncSem2, 0, 0  ) ) < 0 ) {
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

        if ( sem_destroy(&syncSem2 ) < 0 ) {
                perror("sem_destory");
        }

        if ( sem_destroy(&mutexSem) < 0 ) {
                perror("sem_destroy");
        }

}


