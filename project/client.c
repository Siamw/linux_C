#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>

#define BUF_SIZE 128
#define NAME_SIZE 20
#define NOTSET 0
#define EXIST 1
#define NOTEXIST 2


void * send_msg(void * arg);
void * recv_msg(void * arg);
void error_handling(char * msg);

char name[NAME_SIZE]= {NULL};
char msg[BUF_SIZE] = {NULL};
int cli_exist = NOTSET;
int setFName = 0;
int wOk = 1;

//client

//pthread_mutex_t mutx;


int main(int argc, char *argv[])
{
		int sock;
		struct sockaddr_in serv_addr;
		pthread_t snd_thread, rcv_thread;
		void * thread_return;
		if(argc!=4) { // ip주소, port number, user name 순으로 arg받는다.
				printf("Usage : %s IP port name\n", argv[0]);
				exit(1);
		}


		sprintf(name, "%s", argv[3]); // name
		sock=socket(PF_INET, SOCK_STREAM, 0); //ipv4, tcp/ip

		memset(&serv_addr, 0, sizeof(serv_addr));//serv_addr = 0
		serv_addr.sin_family=AF_INET; //고정
		serv_addr.sin_addr.s_addr=inet_addr(argv[1]);//ip address
		serv_addr.sin_port=htons(atoi(argv[2]));//port number

		if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1)//connect socket socket to addr
				error_handling("connect() error");

		write(sock, name, NAME_SIZE);//sock에 name을 보낸다.
		printf("\nconnecting... \n\n ** Open chatting ** \n type \"help\" to see another menu!\n");

		//make thread to send and receive and end
		pthread_create(&snd_thread, NULL, send_msg, (void*)&sock);
		pthread_create(&rcv_thread, NULL, recv_msg, (void*)&sock);
		pthread_join(snd_thread, &thread_return);
		pthread_join(rcv_thread, &thread_return);
		close(sock); // close socket 
		return 0;
}

void * send_msg(void * arg)   // send thread main
{
		int sock=*((int*)arg);
		int Flength = 0;
		int i=0;
		int fSize = 0;
		int fEnd = 0;
		char name_msg[NAME_SIZE+BUF_SIZE] = {NULL};
		char t_msg[BUF_SIZE] = {NULL};
		char last_msg[BUF_SIZE] = {NULL};
		char t_name_msg[BUF_SIZE] = {NULL};
		char noUse[BUF_SIZE] = {NULL};
		const char enter[BUF_SIZE] = {"\n"};


		while(1) 
		{
				if(wOk == 0) {
						sleep(1);
				}

				fgets(msg, BUF_SIZE, stdin);//get message !!



				if(!strcmp(msg,"quit\n")) //if write quit, then close socket
				{
						close(sock);
						exit(0);
				}


				else if(!strcmp(msg, "sendfile\n")) //if send file, 
				{
						char location[BUF_SIZE];
						char who[NAME_SIZE];
						FILE *fp;
						FILE *file;

						printf("File location : ");
						scanf("%s", location);

						file = fopen(location, "rb");//location open
						if(file == NULL) {// 아무것도 없으면
								printf("No file \n");
								continue;
						}

						printf("To who (ID)? : ");//누구에게 보내냐
						scanf("%s", who);

						write(sock,"Hey server! I'll send file\n", BUF_SIZE);
						//서버에게 파일 보낸다고 함
						
						write(sock, who, NAME_SIZE);
						//누구에게 보내는지를 서버에게 알려준다.

						while(cli_exist == NOTSET) {
								sleep(1);
						}

						if(cli_exist == NOTEXIST) {//존재하지않으면
								printf("No user exist \n");
								cli_exist = NOTSET;
								continue;
						} 

						while(1) {   
								fEnd = fread(noUse, 1 , BUF_SIZE, file);//file에서 길이 1로 noUse에 읽음
								fSize += fEnd;

								if(fEnd != BUF_SIZE)
										break;
						}
						fclose(file);

						printf("\nFile transfer start \n(File Size : %d Byte)\n", fSize); 
						write(sock, &fSize, sizeof(int)); // 파일 크기정보 보냄.
						fSize = 0;

						fp = fopen(location, "rb");//파일 염


						while(1) {

								Flength = fread(t_msg, 1 , BUF_SIZE, fp);

								if(Flength != BUF_SIZE) {
										for(i=0; i<Flength; i++) {
												last_msg[i] = t_msg[i];
										} 
										//fread 는 파일끝에 닿았을 때 이전의 데이터와 함쳐짐이 있을 수 있으므로 방지

										write(sock, last_msg, BUF_SIZE);

										write(sock, "FileEnd_cl->sr", BUF_SIZE);
										break;
								}
								write(sock, t_msg, BUF_SIZE); 

						}
						// 서버에 파일의 내용 보냄



						fclose(fp);
						printf("File transfer finish \n");
						cli_exist = NOTSET;


				}
				else if(!strcmp(msg, "file\n")) {

						char location[BUF_SIZE];
						FILE *fp;
						FILE *file;

						printf("File location : ");
						scanf("%s", location);

						file = fopen(location, "rb");
						if(file == NULL) {
								printf("No file like that \n");
								continue;
						}
						// 보낼 파일이 유효한가 확인

						write(sock, "file sending ... \n", BUF_SIZE);
						//먼저 파일을 보낸다는 신호를 서버쪽에 보냄.

						while(1) {   
								fEnd = fread(noUse, 1 , BUF_SIZE, file);
								fSize += fEnd;

								if(fEnd != BUF_SIZE)
										break;
						}
						fclose(file);

						printf("File transfer start \n(File Size : %d Byte)\n", fSize); 
						write(sock, &fSize, sizeof(int)); // 파일 크기정보 먼저 보냄.
						fSize = 0;

						fp = fopen(location, "rb");


						while(1) {

								Flength = fread(t_msg, 1 , BUF_SIZE, fp);

								if(Flength != BUF_SIZE) {
										for(i=0; i<Flength; i++) {
												last_msg[i] = t_msg[i];
										} 
										//ㄴ fread 는 파일끝에 닿았을 때 이전의 데이터와 함쳐짐이 있을 수 있으므로 방지하였음.

										write(sock, last_msg, BUF_SIZE);

										write(sock, "file sended!", BUF_SIZE);
										break;
								}
								write(sock, t_msg, BUF_SIZE); 

						}
						//서버에 파일의 내용을 보냄.      

						fclose(fp);
						printf("File transfer finish \n");      
				} // 전체에게 파일 보냄
				else if(!strcmp(msg, "help\n")) {

						printf("\n \n !!!! HELP !!!!\n");
						printf("모두에게 메세지를 보내려면 그냥 보내면 된다.\n");
						printf("file : 파일 보내기 \n");
						printf("quit : 종료 \n");
						printf("\n\n");

				} // 메뉴를 보고싶을 경우
				else if(setFName == 1) {
						if(strcmp(msg, enter)) {
								setFName = 0;
						}
				} // 한명에게만 메세지를 보내고싶은 경우
				else if(!strcmp(msg,"whisper\n")) {
						char who[NAME_SIZE];
						char wmsg[BUF_SIZE] = {NULL};

						strcpy(t_msg, NULL);

						printf("(!Record) Who(ID) Message : ");
						scanf("%s %[^\n]", who, wmsg);

						write(sock, "whisper : client to server", BUF_SIZE);
						//보낸다는 신호를 먼저 보낸다      

						write(sock, who, NAME_SIZE);//누구에게?

						strcpy(t_msg, "\n");
						sprintf(t_name_msg,"[(only to you) %s] %s", name, t_msg);
						sprintf(name_msg,"[(only to you) %s] %s", name, wmsg);

						name_msg[strlen(name_msg)] = '\n';

						if(strcmp(name_msg, t_name_msg) != 0)//메세지없음 안보냄 
								write(sock, name_msg, BUF_SIZE);

				}
				else 
				{
						strcpy(t_msg, "\n");
						sprintf(t_name_msg,"[%s] %s", name, t_msg);
						sprintf(name_msg,"[%s] %s", name, msg);

						if(strcmp(name_msg, t_name_msg) != 0) 
								write(sock, name_msg, BUF_SIZE);

				}

		}
		return NULL;
}

void * recv_msg(void * arg)   // read thread main
{
		int sock=*((int*)arg);
		char name_msg[BUF_SIZE] = {NULL};
		char file_msg[BUF_SIZE] = {NULL};
		const char signal[BUF_SIZE] = {"file : server to client"};
		const char end_msg[BUF_SIZE] = {"FileEnd_server to client"};
		const char nocl_msg[BUF_SIZE] = {"[NoClient]"};
		const char yescl_msg[BUF_SIZE] = {"[continue]"};
		const char noConnect[BUF_SIZE] = {"USER FULL"};
		int str_len = 0;
		int fSize = 0;

		while(1)
		{
				str_len=read(sock, name_msg, BUF_SIZE);


				if(!strcmp(name_msg, signal)) {

						setFName = 1;
						wOk = 0;

						printf("receive request. ");

						read(sock, &fSize, sizeof(int));
						printf("(File size : %d Byte)\n [press Enter key to continue]", fSize);
						//파일 사이즈 받아 출력하기.

						printf("(!Notice)set file name : ");

						wOk = 1;
						while(setFName == 1) {
								sleep(1);
						}

						msg[strlen(msg)-1] = '\0';

						FILE *fp;
						fp = fopen(msg, "wb"); 

						while(1)
						{      
								read(sock, file_msg, BUF_SIZE);

								if(!strcmp(file_msg, end_msg)) 
										break;
								fwrite(file_msg, 1, BUF_SIZE, fp);
						}

						fclose(fp);

						printf("(!Notice)File receive finished \n");
						//send_msg 쓰레드의 활동 재개


				}
				else if(strcmp(name_msg, yescl_msg) == 0) {

						cli_exist = EXIST;

				}
				else if(strcmp(name_msg, nocl_msg) == 0) {

						cli_exist = NOTEXIST; 
				}
				else if(!strcmp(name_msg, noConnect)) {
						printf("too many users. sorry \n");
						exit(0);
				}
				else {
						fputs(name_msg, stdout);
				}
		}
		return NULL;
}

void error_handling(char *msg)
{
		fputs(msg, stderr);
		fputc('\n', stderr);
		exit(1);
}
