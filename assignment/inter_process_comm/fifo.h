#define MAX_FIFO_NAME 32
#define SERV_FIFO "./.fifo"

typedef struct  { //이렇게 만들어서 쓰면 에러를 줄일 수 있다. 
	char returnFifo[MAX_FIFO_NAME]; // client가 기다리는 fifo의 이름/
	char data[128];//data
}
	MsgType;
