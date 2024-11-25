CFLAGS = -g -O
LTFLAGS = --tag=CC

all:    inc

%.lo:   %.c
	libtool --mode=compile $(LTFLAGS) $(CC) -c $<
libinc.la: lib.lo libg.lo
	libtool --mode=link $(LTFLAGS) $(CC) -o $@ $^ -rpath /usr/lib64
inc:    main.o libinc.la
	libtool --mode=link $(LTFLAGS) $(CC) -o $@ $^
check:  inc
	./$< 123
clean:
	rm -rf *.so inc .libs *.l? *.o
