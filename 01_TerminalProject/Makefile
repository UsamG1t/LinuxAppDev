SRC=curses.c
EXE=curses
CC=cc
LDLIBS=-lncursesw
CFLAGS=-Wall

%:  %.c
	$(CC) $(CFLAGS) $< $(LDLIBS) -o $@

all:	curses

clean:
	rm -f o oo ${EXE} *.o