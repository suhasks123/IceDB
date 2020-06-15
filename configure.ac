AC_PREREQ([2.69])
LT_PREREQ([2.4.6])
AC_INIT([IceDB], [1.0])

AC_CONFIG_SRCDIR([src/ice.cc])
AC_CONFIG_AUX_DIR([build-aux])

dnl AC_SEARCH_LIBS([pow], [m])

dnl Initialize Automake
AM_INIT_AUTOMAKE([subdir-objects 1.15 foreign])

AC_PROG_CXX
AC_CONFIG_MACRO_DIRS([m4])

LT_INIT()

dnl To Check for GNU readline
PKG_CHECK_MODULES([READLINE], [readline], [
    LIBS="$READLINE_LIBS $LIBS"
    CXXFLAGS="$READLINE_CXXFLAGS $CXXFLAGS"
    AC_DEFINE([HAVE_READLINE], [1], [Define if readline is available])
], [
    AC_SEARCH_LIBS([readline], [readline], [
        AC_DEFINE([HAVE_READLINE], [1], [Define if readline is available])
    ], [
        AC_MSG_ERROR([*** readline not found. Please install GNU readline before building.])
    ])
])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile])

AC_OUTPUT