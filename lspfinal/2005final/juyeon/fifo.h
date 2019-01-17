#define MAX_FIFO_NAME	32

#define	myfifo			"./.fifo"

typedef struct  {
	char	returnFifo[MAX_FIFO_NAME];
	char	data[128];
}
	MsgType;

