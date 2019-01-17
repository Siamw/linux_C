#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int t = 0;


void SigIntHandler(int signo)
{
	FILE* f = fopen("print.txt", "wt");
	fprintf(f, "%d\n", t);
	fclose(f);
	exit(0);
}

int main()
{
	int i=1;

	signal(SIGINT, SigIntHandler);

	while(1)
	{
		printf("%d ", i);
		fflush(stdin);
		if( i>=5 ){
			i=0;
			printf("\n");
		fflush(stdin);
		}
		t++;
		i++;
		sleep(1);
	}

	return 0;
}
