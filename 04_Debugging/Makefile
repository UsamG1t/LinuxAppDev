GENS = *.output range
TRASH = *.o 
CFLAGS = -O0 -g
CC = cc

.PHONY: clean distclean

all:	test
	echo "source range1.gdb" | gdb ./range > /dev/null
	cat range1.output | grep '\$' > r1.out

	echo "source range2.gdb" | gdb ./range > /dev/null
	cat range2.output | grep '\$' > r2.out
	

test:	range

range:	range.c
	$(CC) $(CFLAGS) $< -o $@

distclean:
	rm -f $(TRASH)

clean:	distclean
	rm -rf $(GENS)