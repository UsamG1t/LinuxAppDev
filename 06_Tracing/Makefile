GENS = move Hello Bye Errors
TRASH = *.o out_*
CFLAGS = -Wall
CC = cc

.PHONY: clean distclean

all:	test

test:	move
	cp Icon Hello

	-$$(./move 2>> Errors)
	-$$(./move Hello 2>> Errors)
	
	-$$(strace -P Hello -e openat --inject=openat:error=EACCES:when=1 ./move Hello Bye 2>> Errors)
	(ls | grep -E "(Bye)|(Hello)" >> Errors)
	
	-$$(strace -P Bye -e openat --inject=openat:error=EBADF:when=1 ./move Hello Bye 2>> Errors)
	(ls | grep -E "(Bye)|(Hello)" >> Errors)
	
	-$$(strace -P Hello -e read --inject=read:error=EIO:when=3 ./move Hello Bye 2>> Errors)
	(ls | grep -E "(Bye)|(Hello)" >> Errors)
	
	-$$(echo "Something" > Bye)
	-$$(strace -P Bye -e write --inject=write:error=EFBIG:when=5 ./move Hello Bye 2>> Errors)
	(ls | grep -E "(Bye)|(Hello)" >> Errors)
	
	-$$(strace -P Hello -e unlink --inject=unlink:error=EISDIR ./move Hello Bye 2>> Errors)
	(ls | grep -E "(Bye)|(Hello)" >> Errors)
	
	-$$(./move Hello Bye 2>> Errors)
	(ls | grep -E "(Bye)|(Hello)" >> Errors)
	
	cat Errors | grep -E "(: :)|(^Hello)|(^Bye)" > out_grep
	-$$(cmp Icon_grep out_grep)

move.o:	move.c

move:	move.o

distclean:
	rm -f $(TRASH)

clean:	distclean
	rm -rf $(GENS)
