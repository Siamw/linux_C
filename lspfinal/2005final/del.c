#include <stdio.h>

void del( char str[] )
{
	int count = 0;
	int i=0;

	while( str[i] != '\0' )
	{
		str[i] = str[i+1];
		i++;
	}

}

main()
{
	char str[20] = "programming";
	del(str);
	puts(str);
}


