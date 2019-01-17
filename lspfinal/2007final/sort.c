#include <stdio.h>
#include <memory.h>
#include <stdlib.h>


main( int argc, char* argv[] ) { 

	int i,j;
	int *arr;
	int mid;
	int temp;
	int count;

	count = argc -1;

	arr = (int*)malloc( sizeof(int)* count  );

	for( i = 0;  i < count  ; i++ ) 
		arr[i] = atoi(argv[i+1]);

	
	//for( i = 0; i < count ; ++i) 
	//	printf("%d ", arr[i] );
		
	//printf("\n");

	for( i = 0; i < count-1 ; i++ ) {
		mid = i;
		for( j = i+1; j < count; j++ ) { 
			if( arr[mid] > arr[j] ) {
				temp = arr[mid];
				arr[mid] = arr[j];
				arr[j] = temp;
			}
		}
	}

	for( i = 0; i < count; ++i) 
		printf("%d ", arr[i] );





	free( arr );
}
	
	


