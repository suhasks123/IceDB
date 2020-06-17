#ACLOCAL_AMFLAGS = -I m4
include_HEADERS = include/ice.hpp

lib_LTLIBRARIES = libice.la
libice_la_SOURCES = \
 include/hashClass.hpp \
 src/hash.cc \
 src/ice.cc \
 src/Metadata.cc \
 src/Database.cc \
 include/b64.h \
 include/encrypt.h \
 include/vigenere.hpp
libice_la_CPPFLAGS = -I$(top_srcdir)/include


noinst_PROGRAMS = bin/ice_example
bin_ice_example_SOURCES = src/main.cc
bin_ice_example_CPPFLAGS = -I$(top_srcdir)/include
bin_ice_example_LDADD = libice.la

bin_PROGRAMS = bin/ice
bin_ice_SOURCES = src/ice_shell.cc
bin_ice_CPPFLAGS = -I$(top_srcdir)/include
bin_ice_LDADD = libice.la