

int strlen_p(char *str)
{
	int len=0;
	while(*str++) //str포인터 위치에 글자가있으면 true를 반환하여 while문에 들어가고, 포인터를 하나 뒤로 옮긴다.
	{
		len++;//str의 포인터를 하나씩 옮기며 false가 아닐 때 까지 길이를 1씩 늘린다.
	}

	return len;//길이 리턴
}


int strlen_a(char str[])
{
	int i;
	for(i=0;str[i]!='\0';i++)//글자가 있을 때 까지 i를 ++시킨다.
		;
	return i;
}

void strcpy_p(char *dst, char *src)
{
	while(*src){//src에 글자가 있을 때 까지
		*dst++=*src++;//dst에 src의 글자를 입력하고나서 둘 다 포인터를 하나씩 뒤로 옮긴다.
	}
	*dst = *src;//마지막 문자열을 복사하지 않고 while문을 빠져나오기 때문에 넣어준다.
}

void strcpy_a(char dst[], char src[])
{
	int i;
	for(i=0;src[i]!='\0';i++)//src에 글자가 있을 때 까지
		dst[i]=src[i];//i번째 dst에 i번재 src를 넣는다.
	dst[i]=src[i];//마찬가지로 마지막 문자열이 복사되지 않기때문에 넣어준다.
}

void strcat_p(char *dst, char *src)
{
	while(*dst++)// dst에 글자가 있을 때 까지 
		;//뒤로 이동한다.
	*dst--;//맨 뒤에 붙여주어야 하기 때문에 다시 한칸 앞으로 간다.
	while(*src){//src에 글자가 있을 때 까지
		*dst++=*src++;//dst에 src를 붙이고 각각 한칸씩 뒤로옮기며 복사한다. 
	}
	*dst=*src;//마지막 문자열이 복사되지 않기 때문에 넣어준다.
}

void strcat_a(char dst[], char src[])
{
	int i, j;
	for(i=0;dst[i]!='\0';i++)//dst의 마지막까지 이동한다.
		;
	for(j=0;src[j]!='\0';j++)//dst의현위치(i)에 src의 현위치값을 넣어준다.
		dst[i+j]=src[j];
	dst[i+j]=src[j];//마지막 문자열이 복사되지 않기 때문에 넣어준다.
}


int strcmp_p(char *dst, char *src)
{
	while(*dst||*src)//두 문자열 모두 끝이 날 때 까지
	{
		if(*dst>*src){return 1;}//dst의 값이 더 크면 1 리턴
		if(*dst<*src){return -1;}//src의 값이 더 크면 -1 리턴

		*dst++; *src++;//둘이 같아서 위에서 리턴이 안되면 둘 다 다음 포인터로 넘어간다.
	}
	return 0;// 두 문자열 모두 끝날 때 까지 1, -1이 출력되지 않으면 두 문자열이 같다고 판단하고 0을 리턴한다.
}

int strcmp_a(char dst[], char src[])
{
	int i;
	for(i=0;dst[i]!='\0'||src[i]!='\0';i++)// 두 문자열 모두 끝 날 때 까지
	{
	if(dst[i]>src[i]){return 1;}//dst가 더 크면 1
	if(dst[i]<src[i]){return -1;}//src가 더 크면 -1 리턴
	}

	return 0;//두 문자열 모두 끝날 때 까지 1, -1이 출력되지 않으면 두 문자열이 같다고 판단하고 0을 리턴한다.
}


main()
{
	int len1,len2,a,b,c,d;
	char str1[20],str2[20];
	len1 = strlen_p("Hello");
	len2 = strlen_a("Hello");
	printf("strlen: p=%d, a=%d\n",len1,len2);

	strcpy_p(str1,"Hello");
	strcpy_a(str2,"Hello");
    printf("strcpy: p=%s, a=%s\n",str1,str2);

	  strcat_p(str1,"World!");
	  strcat_a(str2,"World!");
	  printf("strcat: p=%s, a=%s\n",str1,str2);

	a=strcmp_p("hello", "hell");
	b=strcmp_a("hell","hello");
	c=strcmp_p("aa","aa");
	d=strcmp_a("bb","bb");
	  printf("strcmp : p=%d,%d, a=%d,%d\n, ",a,c,b,d);
	}



