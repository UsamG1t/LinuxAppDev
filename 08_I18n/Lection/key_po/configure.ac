#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([Key logger], [0.00], [george@altlinux.org])
AM_INIT_AUTOMAKE([foreign subdir-objects])
AM_GNU_GETTEXT(external)
AM_GNU_GETTEXT_VERSION(0.21)
AC_CONFIG_SRCDIR([src/key.c])
AC_CONFIG_HEADERS([config.h])
AC_SUBST(GETTEXT_PACKAGE, "$PACKAGE")
ALL_LINGUAS="ru"

# Checks for programs.
AC_PROG_CC
IT_PROG_INTLTOOL

# Checks for libraries.
AC_CHECK_LIB([ncursesw],[initscr],[],[AC_MSG_ERROR([Curses is needed])])
AC_CHECK_LIB([optional],[completely_lost])

# Checks for header files.
AC_CHECK_HEADERS([unistd.h])
AC_CHECK_HEADER([ncurses.h])

# Optional clues
AC_ARG_ENABLE([keypad],
    AS_HELP_STRING([--enable-keypad], [Enable input ESC-sequences recognition]),
    AC_DEFINE(KEYPAD,[],[ESC-sequences recognition])
  )

AC_ARG_ENABLE([frame],
    AS_HELP_STRING([--enable-frame=width], [Define frame width]),
    AC_DEFINE_UNQUOTED(DX,[$enable_frame],[Frame width])
  )

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE

AC_CONFIG_FILES([Makefile po/Makefile.in])
AC_OUTPUT
