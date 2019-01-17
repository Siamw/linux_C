#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BUF_SIZE 256

char Mysl[100][6];


void sort( int argc, char* argv[] ) {

		int i,j;
		int *arr;
		int mid;
		int temp;
		int count;

		count = argc -1;

		arr = (int*)malloc( sizeof(int)* count  );

		for( i = 0;  i < count  ; i++ )
				arr[i] = atoi(argv[i+1]);

		printf("%d ", arr[i] );

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




void dataAll(char *dentry_name, char *argv);
char *my_strcat(const char *str1, const char *str2);

int main(int argc, char *argv[])
{
 DIR *dp;//디렉토리 변수
 struct dirent *dep;//오픈한 디렉토리를 받아올 구조체
int i =0;

 if((dp=opendir("."))==NULL){//현재디랙토리
 	perror("opendir");
	exit(1);
	}

 while(dep = readdir(dp)){//디렉토리 읽기
 	if(dep->d_ino != 0)//아이노드가 0이 아니면
	dataAll(dep->d_name,".");//현재 파일 dataAll
	}

	for(i =0;i<10;i++)
	{
		if(Mysl[i][3]!=NULL)
		printf("%d",Mysl[i][3]);
	}






	closedir(dp);
}

char *my_strcat(const char *str1, const char *str2)
{
	char *rev = (char *)malloc(strlen(str1)+strlen(str2)+1);//메모리 할당
	int i = 0;//임시 변수

	while(*str1){//첫번째 매개변수 더하기
	rev[i++]=*str1++;}

	rev[i++]='/';

	while(*str2){
	rev[i++]=*str2++;//두번째 매개변수 더하기
	}

	rev[i] = '\0';

	return rev;
}

int cc = 0 ;//개수 

void dataAll(char *dentry_name, char *argv) {
  
    int return_stat;//파일 정보 반환값을 받을 변수
	struct tm *tminfo;//날짜 표기 위한 구조체
	struct stat file_info;//아이노드 블록의 정보를 받아올 변수
	struct passwd *my_passwd; //소유자 구조체
	struct group  *my_group; //그룹 사용자 구조체
	mode_t file_mode;//파일 모드(사용자, 그룹 사용자, 그외 사용자)
	


	char file_name[BUF_SIZE];//경로명 받을 변수
	sprintf(file_name, "%s/%s", argv, dentry_name);//경로 + 파일명


	if ((return_stat = stat(file_name, &file_info)) == -1)	{
		printf(" error\n");
		exit(0);
	}

  	file_mode = file_info.st_mode; 
    
		  
	tminfo = localtime (&(file_info.st_mtime));

	Mysl[cc][0]=tminfo->tm_mon;
	Mysl[cc][1]=tminfo->tm_mday;
	Mysl[cc][2]=tminfo->tm_hour;
	Mysl[cc][3]=tminfo->tm_min;
	//Mysl[cc][4]=dentry_name;

	printf("%d %d %d:%d ",tminfo->tm_mon,tminfo->tm_mday,tminfo->tm_hour,tminfo->tm_min);
	printf("%s", dentry_name);
				     
	printf("\n");

	cc = cc+1;


	}
																																															  
