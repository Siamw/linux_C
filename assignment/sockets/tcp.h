#define MY_ID 0

#define SERV_TCP_PORT 7049
#define SERV_HOST_ADDR "127.0.0.1"//다른 컴퓨터에서 돌리면 이렇게 하드코딩해놓으면 안돌아간다.

#define MSG_REQUEST 1
#define MSG_REPLY 2


typedef struct  {
int type;
char data[128];
}
MsgType;
