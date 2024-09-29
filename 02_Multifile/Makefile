GENS = prog prog-a prog-so liboutput_static.a liboutput.so
TRASH = *.o *~ o.* out_*
CFLAGS = -Wall -fPIC
CC = cc

.PHONY: clean trash_clean
.SECONDARY:	fun.o const.o
.INTERMEDIATE:	liboutput_static.a(fun.o const.o)

all:	test

test:	prog prog-a prog-so
	./prog >> out_prog 2>>out_prog
	./prog a >> out_prog 2>>out_prog
	./prog a v >> out_prog 2>>out_prog
	./prog-a >> out_prog-a 2>>out_prog-a
	./prog-a a >> out_prog-a 2>>out_prog-a
	./prog-a a v >> out_prog-a 2>>out_prog-a
	LD_LIBRARY_PATH=`pwd` ./prog-so >> out_prog-so 2>>out_prog-so
	LD_LIBRARY_PATH=`pwd` ./prog-so a >> out_prog-so 2>>out_prog-so
	LD_LIBRARY_PATH=`pwd` ./prog-so a v >> out_prog-so 2>>out_prog-so
	
	cmp out_prog out_prog-a
	cmp out_prog-a out_prog-so
	cmp out_prog-so out_prog

liboutput_static.a:	liboutput_static.a(fun.o const.o)

liboutput.so:	fun.o const.o
	$(CC) $^ -o $@ -shared

fun.o prog.o:	outlib.h

prog:	prog.o const.o fun.o

prog-a:	prog.o liboutput_static.a
	$(CC) $(CFLAGS) -L. -loutput_static $^ -o $@

prog-so:	prog.o liboutput.so
	$(CC) $(CFLAGS) $^ -o $@

trash_clean:
	rm -f $(TRASH)

clean:	trash_clean
	rm -rf $(GENS)