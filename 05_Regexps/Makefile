GENS = esub
TRASH = *.o out_*
CFLAGS = -Wall
CC = cc

.PHONY: clean distclean

all:	test

test:	esub
	./esub 'ab' 'AB' 'zxcv_ab_qwer' > out_esub
	echo "zxcv_ab_qwer" | sed -E 's/ab/AB/' > out_sed
	cmp out_esub out_sed

	./esub '(ab)(not)' '\2 \1' 'There is abnot' > out_esub
	echo "There is abnot" | sed -E 's/(ab)(not)/\2 \1/' > out_sed
	cmp out_esub out_sed

# 	echo "I will back on Sun Oct 20 MSK 2024" | sed -E 's/S([Ocnut ]+)([[:digit:]]*)(.*)([024]{4})/\2th day with \4 warriors/' > out_sed
# 	./esub 'S([Ocnut ]+)([[:digit:]]*)(.*)([024]{4})' '\2th day with \4 warriors' 'I will back on Sun Oct 20 MSK 2024' > out_esub
# 	cmp out_esub out_sed

esub.o:	esub.c

esub:	esub.o

distclean:
	rm -f $(TRASH)

clean:	distclean
	rm -rf $(GENS)