SRC=Show.c
EXE=Show
CC=cc
LDLIBS=-lncursesw
CFLAGS=-Wall

all:	Show

%:  %.c
	$(CC) $(CFLAGS) $< $(LDLIBS) -o $@

clean:
	rm -f o oo ${EXE} *.o