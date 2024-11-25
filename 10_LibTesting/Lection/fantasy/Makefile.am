SUBDIRS = src tests

demo:	all
	./src/namegen '!BVCs !DdM'

checklog:	check
	cat tests/*.log

gcov:	check
	$(MAKE) $(MAKEFLAGS) -C src gcov