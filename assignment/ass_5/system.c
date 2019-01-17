#include <stdio.h>
#include <stdlib.h>

main()
{
	int status;

	if ((status = system("date")) < 0)  {//날짜 출력
		perror("system");
		exit(1);
	}
	
	printf("exit status = %d\n", status);

	if ((status = system("nosuchcommand")) < 0)  {//no such command
		perror("system");
		exit(1);
	}

	printf("exit status = %d\n", status);

	/* $ who; exit 44 */
	if ((status = system("who; exit 44"))<0)  {//logout
		perror("system");
		exit(1);
	}
	
	printf("exit status = %d\n", status);
}

