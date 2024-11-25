TESTS_ENVIRONMENT = CK_VERBOSITY=$(CK_VERBOSITY)
TESTS = dummy
check_PROGRAMS = dummy

.ts.c:
	checkmk $< > $@

AM_CFLAGS = -I$(top_builddir)/src @CHECK_CFLAGS@
LDADD = $(top_builddir)/src/libnamegen.la @CHECK_LIBS@