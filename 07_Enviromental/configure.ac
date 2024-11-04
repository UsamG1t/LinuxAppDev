#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.72])
AC_INIT([Key Logger], [0.0], [Stephen])
AC_CONFIG_SRCDIR([rhasher.c])
# AM_INIT_AUTOMAKE([foreign subdir-objects])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([rhash],[rhash_library_init],[],[AC_MSG_ERROR([Rhash is needed])])
AC_CHECK_LIB([readline],[readline], [], [AC_MSG_ERROR([Readline is needed])])

# Checks for header files.
AC_CHECK_HEADERS([errno.h])
AC_CHECK_HEADERS([string.h])
AC_CHECK_HEADERS([stdlib.h])
AC_CHECK_HEADERS([readline/readline.h])
AC_CHECK_HEADERS([readline/history.h])
AC_CHECK_HEADERS([rhash.h])


# Optional clues
AC_ARG_ENABLE([keypad],
    AS_HELP_STRING([--without-readline], [Enable force input without readline]),
    AC_DEFINE(NO_READLINE,[1],[Input without readline])
  )


# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([strerror])

# AC_CONFIG_FILES([Makefile])
AC_OUTPUT
