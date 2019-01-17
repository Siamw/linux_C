#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define MAXBUF 128
#define MAXCLIENT 5
#define MAXNAME 20

void *send_message (void * arg);
void send_chat(char * msg, int len);

int client_count = 0;
int client_socks [MAXCLIENT];
char client_name [MAXNAME] = {NULL};
char client_names [MAXCLIENT][MAXNAME] = {NULL};

pthread_mutex_t mutex;

int main(int argc, char *argv[])
{
		int server_sock, client_sock, i;
		struct sockaddr_in server_addr, client_addr;
		int client_addr_size;
		pthread_t tid;


		if(argc != 2)
		{
				printf("Usage : %s port\n", argv[0]);
				exit(1);
		}

		pthread_mutex_init (&mutex, NULL);      // 뮤텍스 생성
		server_sock = socket (PF_INET, SOCK_STREAM, 0);   // 소켓 생성

		// 초기화
		memset (&server_addr, 0, sizeof(server_addr));
		server_addr.sin_family = AF_INET; 
		server_addr.sin_addr.s_addr = htonl (INADDR_ANY);
		server_addr.sin_port = htons (atoi (argv[1]));

		if (bind(server_sock, (struct sockaddr*) &server_addr, sizeof(server_addr)) == -1)
		{
				perror("bind");
				exit(1);
		}

		if (listen(server_sock, 5) == -1)
		{
				perror("listen");
				exit(1);
		}

		while(1)
		{
				client_addr_size = sizeof (client_addr);
				client_sock = accept (server_sock, (struct sockaddr*)&client_addr, &client_addr_size);

				if (client_count >= MAXCLIENT)
				{
						printf("connect fail...\n", client_sock);
						write (client_sock, "too many user..", MAXBUF);
						continue;
				}

				pthread_mutex_lock (&mutex);         // 뮤텍스 락

				client_socks [client_count] = client_sock;
				read (client_sock, client_name, MAXNAME);      
				strcpy (client_names [client_count ++], client_name);   // 클라이언트들의 이름 설정

				pthread_mutex_unlock (&mutex);

				// 스레드 생성
				pthread_create(&tid, NULL, send_message, (void*)&client_sock);
				pthread_detach(tid);
				printf ("connected client : %s \n", inet_ntoa(client_addr.sin_addr));
		}

		close(server_sock);   // 소켓 종료
		return 0;
}

void * send_message (void * arg)
{
		int client_sock = *((int*) arg);
		int str_len = 0, i;
		int file_size = 0;
		const char transfer_one [MAXBUF] = {"[파일 전송]"};
		const char transfer_end [MAXBUF] = {"[파일 전송 완료]"};
		const char transfer_all [MAXBUF] = {"[모두에게 파일 전송]"};
		char message [MAXBUF] = {NULL};
		char file_message [MAXBUF] = {NULL};

		while ((str_len = read (client_sock, message, MAXBUF)) != 0)
		{

				if (!strcmp (message, transfer_one))      // 한명에게만 파일 전송시
				{
						int j;
						int fault = 0;
						int dest_num = NULL;
						char temp [MAXNAME]= {NULL};

						read (client_sock, temp, MAXNAME);

						pthread_mutex_lock(&mutex);

						for (j = 0; j < client_count; j ++)
						{   // 파일을 전송할 대상이 존재하는지 체크
								if (!strcmp (temp, client_names [j]) )
								{
										fault = 0;
										dest_num = j; // 보낼 소켓 번호를 저장
										break;
								}
								else if (j == client_count - 1)
								{
										fault = 1; // 그런 사용자가 없을 때 표시
										break;
								}
						}

						// 대상의 존재 유무에 따라 결과 수행
						if (fault == 1)
						{
								write (client_sock, "해당 사용자는 존재하지 않습니다..", MAXBUF);
								pthread_mutex_unlock (&mutex);
								continue;
						}
						else if (fault == 0)
						{
								write (client_sock, "전송을 시작하겠습니다..", MAXBUF);
						}

						write (client_socks [dest_num], "파일 전송을 시작합니다.", MAXBUF);   // 대상에게 파일을 전송하겠다고 알려준다


						read (client_sock, &file_size, sizeof (int));
						printf ("파일 크기 : %d Byte\n", file_size);
						write (client_socks [dest_num], &file_size, sizeof (int));         // 파일의 크기를 알려준다.

						while (1)
						{
								read (client_sock, file_message, MAXBUF);
								if (!strcmp(file_message, transfer_end))
										break;

								write (client_socks [dest_num], file_message, MAXBUF);
						}
						write(client_socks [dest_num], "파일 전송을 완료했습니다", MAXBUF);

						pthread_mutex_unlock (&mutex);

						printf("(!) 파일을 전송했습니다.\n");

				}
				else if (!strcmp (message, transfer_all))         // 모든 사용자에게 파일 전송시
				{
						pthread_mutex_lock (&mutex);

						for (i = 0; i < client_count; i ++)
						{
								if (client_sock == client_socks [i])
										continue;

								write (client_socks [i], "파일 전송을 시작합니다.", MAXBUF);      // 대상에게 파일을 전송하겠다고 알려준다
						}

						read (client_sock, &file_size, sizeof(int));
						printf ("파일 크기 : %d Byte\n", file_size);

						for(i = 0; i < client_count; i ++)
						{
								if(client_sock == client_socks[i])
										continue;

								write(client_socks[i], &file_size, sizeof(int));         // 파일의 크기를 알려준다.
						}

						while(1)
						{
								read (client_sock, file_message, MAXBUF);

								if (!strcmp (file_message, transfer_end))
										break;

								for(i = 0; i < client_count; i ++)
								{
										if(client_sock == client_socks [i])
												continue;

										write (client_socks [i], file_message, MAXBUF);
								}
						}

						for(i = 0; i < client_count; i ++)
						{
								if (client_sock == client_socks [i])
										continue;

								write(client_socks[i], "파일 전송을 완료했습니다.", MAXBUF);
						}
						pthread_mutex_unlock(&mutex);

						printf ("(!) 파일을 전송했습니다 \n");
				}
				else      // 채팅메시지 전송
				{
						send_chat(message, str_len);
				}
		}


		pthread_mutex_lock (&mutex);

		for (i = 0; i < client_count; i ++)   // 연결을 종료한 클라이언트들은 없앤다.
		{
				if (client_sock == client_socks [i])
				{
						while (i ++ < client_count - 1)
						{
								client_socks [i] = client_socks [i + 1];
								strcpy (client_names [i], client_names [i + 1]);
						}
						break;
				}
		}
		client_count --;

		pthread_mutex_unlock (&mutex);      // 뮤텍스 언락

		close (client_sock);   // 소켓 닫기
		return ;
}

void send_chat (char * chat, int length)
{   // 채팅 메시지 보내기

		int i;

		pthread_mutex_lock (&mutex);

		for (i = 0; i < client_count; i ++)
		{
				write(client_socks [i], chat, MAXBUF);
		}

		pthread_mutex_unlock (&mutex);
}
