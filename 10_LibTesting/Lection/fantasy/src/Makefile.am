CFLAGS = -ansi -pedantic -Wall -Wextra
if COND_GCOV
CFLAGS  += -O0 -g -fprofile-arcs -ftest-coverage
else
CFLAGS  += -O3 -g3
endif

lib_LTLIBRARIES = libnamegen.la
bin_PROGRAMS = namegen

namegen_LDADD = libnamegen.la

libnamegen.c: const.h

const.h: tablegen.py
	python3 $< > $@

gcov:
	gcov -o .libs libnamegen -t -k -b | egrep -v '[[:digit:]]:[ /][*]'