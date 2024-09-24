.PHONY: clean distclean
GENS = prog libout.so
TRASH = *.o *~ o.*
CFLAGS = -Wall -fPIC

all:	prog README

fun.o prog.o:	outlib.h

libout.so:	fun.o const.o
	$(CC) $^ -o $@ -shared

prog:   prog.o libout.so

README:	prog
	LD_LIBRARY_PATH=`pwd` ./$< > $@ 2>&1

clean:
	rm -f $(TRASH)

distclean:	clean
	rm -rf $(GENS)