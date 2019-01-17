#define MY_ID			37

#define	SERV_TCP_PORT	(17000 + MY_ID)
#define	SERV_HOST_ADDR	"127.0.0.1"

#define	MSG_REQUEST		1
#define	MSG_REPLY		2
#define MAX_BUF			1024;


typedef struct  {
	int		type;
	char    fileName[16];
	char	data[4096];
}
	MsgType;


