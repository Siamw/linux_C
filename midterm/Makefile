C = gcc
CFLAGS =
LDFLAGS = -lpthread

.SUFFIXES : .c .o
.c.o :
	$(CC) -c $(CFLAGS) $<

ALL = add

all: $(ALL)

add : add.o
	$(CC) -o $@ $< $(LDFLAGS)

clean :
	rm -rf *.o $(ALL)
