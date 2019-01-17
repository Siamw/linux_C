#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
	int n, i, j;
	
	if( argc != 2 ){
		printf("\n	Usage: %s <Integer>\n\n", argv[0]);
		exit(1);
	}

	n = atoi(argv[1]);

	for(i=0; i<=n/2; i++)
	{
		for(j=0; j<=n; j++)
		{
			if( j>=i && j<=n-i )
				printf("%d ", j);
			else
				printf("- ");
		}
		printf("\n");
	}

	return 0;
}
