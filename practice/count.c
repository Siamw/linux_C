#include<stdio.h>
#include<string.h>


int main(int argc, char *argv[])
{

	FILE *src;
	char ch;
	int count =0;

	if((src=fopen(argv[1],"rt"))==NULL){
		perror("fopen");
		exit(1);
	}

	while((ch=fgetc(src)) != EOF){
	if(ch==' '||ch=='\n')
		count++;
	}
	
	printf("%d ",count);
	return 0;

}
