CFLAGS = -Wall -O0 -g
AM_CPPFLAGS = -D'LOCALEDIR="$(localedir)"'

bin_PROGRAMS=key

key_SOURCES=src/key.c

SUBDIRS = po

TESTS = isterm.sh

isterm.sh:
	echo 'test "`./key < /dev/null 2>&1`" = "./key: Not a terminal"' > $@
	chmod +x $@

gitclean:
	git clean -xdf
