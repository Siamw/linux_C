#include<stdio.h>
#include<string.h>

void strupper(char str[]){

	int ch=0;

	while(str[ch]!='\0'){
			if( str[ch]>='a'&& str[ch]<='z')
			{
				str[ch]=str[ch]-32;
			}
			ch++;
			printf("%c",str[ch-1]);
		}	
}
int main()
{
	char hi[100]="Hello, worLd!";


	strupper(hi);

	return 0;
}
