#include<stdio.h>

/*
void conv(char str[])
{
     int i, count=0;
     int end;
     char temp[20];

     while( str[count] != 0 ) {
	  count++;
     }

     end = count-1;

     for(i=0;i<count;i++)
     {
	  temp[i] = str[end--]; 
     }
     
     for(i=0;i<count;i++)
     {
	  str[i] = temp[i];
     }
}
*/

void conv( char* str ) { 
	int length = 0;
	int i;
	char temp[20];
	
	for( i = 0; str[i] != '\0'; ++i ) 
		length++;

	for( i = 0; i < length; ++i ) 	
		temp[i] = str[length-1-i]; 

	temp[i] = '\0';

	for( i = 0; i <= length; ++i ) 
		str[i] = temp[i];

}


main()
{
     char str[20] = "Hello";
     conv(str);
     puts(str);
}
