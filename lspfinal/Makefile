CC = gcc
CFLAGS =
LDFLAGS =# -lsocket -lnsl

.SUFFIXES : .c .o
.c.o :
	$(CC) -c $(CFLAGS) $<

ALL = show print cmd_p fifos fifoc rtts rttc

all: $(ALL)

show: show.o
	$(CC) -o $@ $?

print: print.o
	$(CC) -o $@ $?

cmd_p: cmd_p.o
	$(CC) -o $@ $?

fifos: fifos.o
	$(CC) -o $@ $?

fifoc: fifoc.o
	$(CC) -o $@ $?

rtts: rtts.o
	$(CC) -o $@ $? $(LDFLAGS)

rttc: rttc.o
	$(CC) -o $@ $? $(LDFLAGS)

clean :
	rm -rf *.o *.txt $(ALL)
