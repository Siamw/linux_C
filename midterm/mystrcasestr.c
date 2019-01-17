#include <stdio.h>

char upper(char str){ // 다 대문자로 만들어서 변경
		if(str>='a' && str<='z')//소문자면
		{
			str = str-32;//대문자로 바꿈
		}
		
	return str;
}

char* mystrcasestr(char str1[], char str2[])
{
	int i;
	int j;
	int k;

	for(i = 0; str1[i] != '\0'; i++){
		if(upper(str1[i])==upper(str2[0]))//같으면`
		{
			for(j=i, k=0; upper(str1[j]) == upper(str2[k]);j++,k++){//그 위치에서부터 같을 때 까지
				if(str2[k+1] == '\0'){//그 다음께 null이면
					return str1 + i ;//str1의 i번째 위치를 리턴한다.
				}
			}
		}
	}

	return NULL; //같은 것이 발견되지 않은 경우 null return 
}

main()
{
	char str[] = "Hello hello HELLO";
	char *p;
	p=str;

	while(p){
		p = mystrcasestr(p,"hello");//hello가 들어가는 것 p에 리턴
		if(p != NULL){
			puts(p);//출력
			p++;
		}
	}
}
